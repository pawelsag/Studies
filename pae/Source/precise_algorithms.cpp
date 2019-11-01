#include "precise_algorithms.hpp"
#include "path_manager.hpp"
#include "permutation.hpp"
#include <limits.h>

namespace TSP::PRECISE{
	tsp64_t brutforce(matrix<tsp64_t>& m){
	  	auto series = TSP::path_manager::generate_natural_series(m.n);
	  	tsp64_t current_cost, best_cost = std::numeric_limits<tsp64_t>::max(); 
	  	while(TSP::next_permutation(&series.front(), &series.back())){
	  		auto current_cost = TSP::path_manager::calculate_cost(series, m);
	  		if(best_cost > current_cost)
	  			best_cost = current_cost;
	  	}
	  	return best_cost;
	}

	tsp64_t branch_and_bound(matrix<tsp64_t>& M){
		return 0;
	}
}