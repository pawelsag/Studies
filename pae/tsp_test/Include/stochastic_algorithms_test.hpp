#pragma once
#include <internals.hpp>
#include <tsp_types.hpp>
#include <fstream>
#include <atomic>
#include <mutex>

#define TEST_SA
#define TEST_TABU

namespace TSP::TEST
{
	class stochastic_algorithms_tester
	{
		std::atomic<size_t> taken_threads = 0;
		std::mutex io_mutex;
		void simulated_annealing_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);
		
		void tabu_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);

	public:
		void run();
		std::atomic<size_t> brut_realize_count=0;
		std::atomic<size_t> bb_realize_count =0;
	};
};