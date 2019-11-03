#include <precise_algorithms_test.hpp>
#include <precise_algorithms.hpp>
#include <chrono>
#include <thread> 

namespace TSP::TEST
{	// var defined during cmake building process
	constexpr size_t MAX_THREADS_COUNT = THREAD_COUNT;

	void precise_algorithms_tester::run()
	{
		auto dir_info = loader::load_directory_files("../dane/SMALL");
		auto results_path = loader::filter_out_results(dir_info);
		
		assert(results_path.length() != 0);

		fmt::print("Path found: {}\n", results_path);
		auto results = loader::load_results(results_path.c_str());


		std::sort(dir_info.begin(), dir_info.end(), 
				  [](std::string &a, std::string &b){ return a < b; });
		
		std::fstream bf_stream("../results/bf_results", std::fstream::out);
		bf_stream << common_header;
		std::fstream bb_stream("../results/bb_results", std::fstream::out);
		bb_stream << common_header;
		std::thread t;
		
#ifdef TEST_BF
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());
			while(taken_threads >= MAX_THREADS_COUNT)
				std::this_thread::sleep_for (std::chrono::seconds(5));
			taken_threads++;
 			t = std::thread(&precise_algorithms_tester::brutforce_test, this, std::ref(bf_stream), m, std::ref(results) ); 
			t.detach();
		}
#endif
		
#ifdef TEST_B_AND_B
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());
			while(taken_threads >= MAX_THREADS_COUNT)
				std::this_thread::sleep_for (std::chrono::seconds(5));
			taken_threads++;
 			t = std::thread(&precise_algorithms_tester::branch_baund_test, this, std::ref(bb_stream), m, std::ref(results)); 
			t.detach();
		}
#endif
		// wait for all jobs...
		while(taken_threads > 0)
			std::this_thread::sleep_for (std::chrono::seconds(5));
	}

	void precise_algorithms_tester::brutforce_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t& r_ref)
	{
		fmt::print("[STARTING THREAD] [FUNCTION: BRUTFORCE_TEST] [DATA : {}] \n",m_ref.source);
		auto start = std::chrono::high_resolution_clock::now();
		auto res = TSP::PRECISE::brutforce(m_ref);
		auto end = std::chrono::high_resolution_clock::now();

		assert(res == r_ref[m_ref.source]);

		std::chrono::duration<double> diff = end-start;
		fmt::print("[{} == {}] ", res, r_ref[m_ref.source]);
		fmt::print("[CORRECT VALUE] [TIME TAKEN : {}]\n", diff.count());

		std::lock_guard<std::mutex> lock(io_mutex);
		fs << m_ref.source << ";" << m_ref.n << ";" <<  diff.count() << "\n";
		taken_threads--;
	}
		
	void precise_algorithms_tester::branch_baund_test(std::fstream& fs , matrix<tsp64_t> m_ref,tsp_results_t& r_ref)
	{
		fmt::print("[STARTING THREAD] [FUNCTION: BRANCH_BAUND_TEST] [DATA : {}] \n",m_ref.source);
		auto start = std::chrono::high_resolution_clock::now();
		TSP::PRECISE::branch_and_bound bb(m_ref);
		auto end = std::chrono::high_resolution_clock::now();

		assert(bb.get_result() == r_ref[m_ref.source]);

		std::chrono::duration<double> diff = end-start;
		fmt::print("[{} == {}] ", bb.get_result(), r_ref[m_ref.source]);
		fmt::print("[CORRECT VALUE] [TIME TAKEN : {}]\n",diff.count());
		std::lock_guard<std::mutex> lock(io_mutex);
		fs << m_ref.source << ";" << m_ref.data.size() << ";" <<  diff.count() << "\n";
		taken_threads--;
	}
	
}
