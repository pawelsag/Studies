#pragma once
#include <internals.hpp>
#include <tsp_types.hpp>
namespace TSP::TEST
{
	class precise_algorithms_tester
	{

		void bruteforce_test(matrix<tsp64_t>& m_ref);
		void branch_baund_test(matrix<tsp64_t>& m_ref);
		void compare_results(const char*file);
	public:
		void run();
	};
}