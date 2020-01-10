#include <genetic_algorithms_test.hpp>
#include <genetic_algorithm.hpp>
#include <ant_colony.hpp>
#include <chrono>
#include <thread>
constexpr int PROBES = 10;
using TSP::GENETIC::SELECTION_METHOD;
using TSP::GENETIC::CROSS_METHOD;
using TSP::GENETIC::MUTATION_METHOD;
using TSP::GENETIC::ANT_COLONY_ALG;

namespace TSP::TEST
{	// var defined during cmake building process
	constexpr size_t MAX_THREADS_COUNT = THREAD_COUNT/2-1 <= 0 ? 1 : THREAD_COUNT/2-1;

	void genetic_algorithms_tester::run()
	{
		auto dir_info = loader::load_directory_files("../dane/TSP/TSP");
		auto results_path = loader::filter_out_results(dir_info);
		
		assert(results_path.length() != 0);

		fmt::print("Path found: {}\n", results_path);
		auto results = loader::load_results(results_path.c_str());

		std::sort(dir_info.begin(), dir_info.end(), 
				  [](std::string &a, std::string &b){ return a < b; });
		

#ifdef GENETIC_BASE
		std::fstream ga_stream("../results/ga_results", std::fstream::out);
		if(!ga_stream.is_open() ) {
			abort();
		}
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());

			taken_threads++;
 			genetic_test(std::ref(ga_stream), m, std::ref(results) );
		}
#endif
#ifdef ANT_COLONY
		std::fstream ac_stream("../results/ac_results", std::fstream::out);
		if (!ac_stream.is_open())
		{
			abort();
		}
		for(auto & f : dir_info){
			const auto &m = loader::load(f.c_str());
 			ant_colony_test(std::ref(ac_stream), m, std::ref(results));
		}
#endif

	}

	void genetic_algorithms_tester::genetic_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t& r_ref)
	{
		fmt::print("[STARTING THREAD] [FUNCTION: GENETIC ALGORITHM] [DATA : {}] \n",m_ref.source);
		double tot_time=0.0;
		tsp64_t tot_res=0, res;
		std::chrono::duration<double> diff;
		for(int i =0 ; i < PROBES; i++){
			auto start = std::chrono::high_resolution_clock::now();
			GENETIC::genetic_algorithm<SELECTION_METHOD::RANK,
                                  			CROSS_METHOD::OX,
                                  			MUTATION_METHOD::INSERTION> ga(m_ref);
			auto end = std::chrono::high_resolution_clock::now();
			res = ga.get_result();
			tot_res += res;
			diff = end-start;
			tot_time += diff.count();
		}
		tot_res /= PROBES; 
		tot_time /= PROBES; 
		double res_diff = ( (tot_res - r_ref[m_ref.source])/(double)r_ref[m_ref.source])*100;
		fmt::print("[{} == {}] ", tot_res, r_ref[m_ref.source]);
		fmt::print("[CORRECT VALUE] [TIME TAKEN : {}]\n", tot_time);

		taken_threads--;
		brut_realize_count++;

		std::lock_guard<std::mutex> lock(io_mutex);
		auto s = fmt::format("{} & & {:.2f} & {} & {} & {:.2f} \\\\\n",m_ref.n,tot_time,tot_res, r_ref[m_ref.source],res_diff); // latex format {n , time_avg, res_avg, correct_val, diff in %}
		fs << s;
	}
		
	void genetic_algorithms_tester::ant_colony_test(std::fstream& fs , matrix<tsp64_t> m_ref,tsp_results_t& r_ref)
	{
		fmt::print("[STARTING THREAD] [FUNCTION: ANT COLONY] [DATA : {}] \n",m_ref.source);
		double tot_time=0.0;
		tsp64_t tot_res=0, res;
		std::chrono::duration<double> diff;
		for(int i =0 ; i < PROBES; i++){
			auto start = std::chrono::high_resolution_clock::now();
			TSP::GENETIC::ant_colony<ANT_COLONY_ALG::QAS> ac(m_ref);
			auto end = std::chrono::high_resolution_clock::now();
			res = ac.get_result();
			tot_res += res;
			diff = end-start;
			tot_time += diff.count();
		}
		tot_res /= PROBES;
		tot_time /= PROBES; 
		double res_diff = ( (tot_res - r_ref[m_ref.source])/(double)r_ref[m_ref.source])*100;
		fmt::print("[{} == {}] ", tot_res, r_ref[m_ref.source]);
		fmt::print("[CORRECT VALUE] [TIME TAKEN : {}]\n", tot_time);

		taken_threads--;
		brut_realize_count++;

		std::lock_guard<std::mutex> lock(io_mutex);
		auto s = fmt::format("{} & & {:.2f} & {} & {} & {:.2f} \\\\\n",m_ref.n,tot_time,tot_res, r_ref[m_ref.source],res_diff); // latex format {n , time_avg, res_avg, correct_val, diff in %}
		fs << s;
	}
	
}
