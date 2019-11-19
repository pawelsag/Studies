#pragma once
#include <internals.hpp>
#include <tsp_types.hpp>
#include <fstream>
#include <atomic>
#include <mutex>

// #define TEST_BF
#define TEST_B_AND_B
constexpr const char * common_header = "file_name;data_size;time";

namespace TSP::TEST
{
	class precise_algorithms_tester
	{
		std::atomic<size_t> taken_threads = 0;
		std::mutex io_mutex;
		void brutforce_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);
		
		void branch_baund_test(std::fstream& fs ,matrix<tsp64_t> m_ref,tsp_results_t & r_ref);

	public:
		void run();
	};
};