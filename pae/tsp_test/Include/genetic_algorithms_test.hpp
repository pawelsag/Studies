#pragma once
#include <internals.hpp>
#include <tsp_types.hpp>
#include <fstream>
#include <atomic>
#include <mutex>

#define GENETIC_BASE
// #define ANT_COLONY

namespace TSP::TEST
{
	class genetic_algorithms_tester
	{
		std::atomic<size_t> taken_threads = 0;
		std::mutex io_mutex;
		void genetic_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);
		
		void ant_colony_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);

	public:
		void run();
		std::atomic<size_t> brut_realize_count=0;
		std::atomic<size_t> bb_realize_count =0;
	};
};