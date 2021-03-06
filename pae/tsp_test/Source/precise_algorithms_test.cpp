#include <precise_algorithms_test.hpp>
#include <precise_algorithms.hpp>
#include <chrono>
#include <thread>
 
constexpr const char * common_header = "file_name;data_size;Result;time";
namespace TSP::TEST
{	// var defined during cmake building process
	constexpr size_t MAX_THREADS_COUNT = THREAD_COUNT/2-1 <= 0 ? 1 : THREAD_COUNT/2-1;

	void precise_algorithms_tester::run()
	{
		auto dir_info = loader::load_directory_files("../dane/TSP/TSP");
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
		if (!bb_stream.is_open() ||!bf_stream.is_open() ) {
			abort();
		}

		std::thread t;

		
		const size_t max_test_size = dir_info.size(); 
#ifdef TEST_BF
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());
			while(taken_threads >= MAX_THREADS_COUNT){
				std::this_thread::sleep_for (std::chrono::seconds(5));
				if(brut_realize_count == max_test_size)
					goto step_2;
			}

			taken_threads++;
 			t = std::thread(&precise_algorithms_tester::brutforce_test, this, std::ref(bf_stream), m, std::ref(results) ); 
			t.detach();
		}
	step_2:;
#endif
#ifdef TEST_B_AND_B
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());
			while(taken_threads >= MAX_THREADS_COUNT){
				std::this_thread::sleep_for (std::chrono::seconds(5));
				if(bb_realize_count == max_test_size)
					goto step_exit;

			}
			taken_threads++;
 			t = std::thread(&precise_algorithms_tester::branch_baund_test, this, std::ref(bb_stream), m, std::ref(results)); 
			t.detach();
		}
	step_exit:;
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

		taken_threads--;
		brut_realize_count++;

		std::lock_guard<std::mutex> lock(io_mutex);
		fs << m_ref.source << ";" << m_ref.n << ";" <<  diff.count() << std::endl;
	}
		
	void precise_algorithms_tester::branch_baund_test(std::fstream& fs , matrix<tsp64_t> m_ref,tsp_results_t& r_ref)
	{
		fmt::print("[STARTING THREAD] [FUNCTION: BRANCH_BAUND_TEST] [DATA : {}] \n",m_ref.source);
		auto start = std::chrono::high_resolution_clock::now();
		TSP::PRECISE::branch_and_bound bb(m_ref);
		auto end = std::chrono::high_resolution_clock::now();

		bb.show_results();
		
		assert(bb.get_result() == r_ref[m_ref.source]);

		std::chrono::duration<double> diff = end-start;
		fmt::print("[{} == {}] ", bb.get_result(), r_ref[m_ref.source]);
		fmt::print("[CORRECT VALUE] [TIME TAKEN : {}]\n",diff.count());
		
		taken_threads--;
		bb_realize_count++;

		std::lock_guard<std::mutex> lock(io_mutex);
		fs << m_ref.source << ";" << m_ref.data.size() << ";" <<  diff.count() << std::endl;
	}
	
}
