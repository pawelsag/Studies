#include "precise_algorithms.hpp"
#include "path_manager.hpp"
#include "utils.hpp"
#include <algorithm>
#include <limits.h>

namespace TSP::PRECISE
{
	tsp64_t brutforce(const matrix<tsp64_t>& m){
	  	auto series = TSP::path_manager::generate_natural_series(m.n);
	  	tsp64_t best_cost = std::numeric_limits<tsp64_t>::max(); 
	  	while(TSP::next_permutation(&series.front(), &series.back())){
	  		auto current_cost = TSP::path_manager::calculate_cost(series, m);
	  		if(best_cost > current_cost)
	  			best_cost = current_cost;
	  	}
	  	return best_cost;
	}


	void branch_and_bound::solve(index_t l){
		
		if(l == this->m_ref.n)
		{
			// fmt::print("Level {}", l);
			auto total_cost = this->current_cost + 
								 this->m_ref.get_value(this->current_path[l-1], this->current_path[0]); 
			if(total_cost < final_cost)
			{
				final_cost = total_cost; 	
			}
			return;
		}

		for(index_t i =0 ; i < this->m_ref.n; i++)
		{
			if(this->visited[i] == true || 
			   this->m_ref.get_value(this->current_path[l-1], i) == -1 )
				continue;
			
			
			this->current_cost += this->m_ref.get_value(this->current_path[l-1], i);

			auto cost_estimation = this->calculate_lower_bound(l);

			if( this->current_cost + cost_estimation < final_cost )
			{
				this->current_path[l] = i;
				this->visited[i] = true;
				this->solve(l+1);
			}

			this->current_cost -= this->m_ref.get_value(this->current_path[l-1], i);
			
			std::memset(this->visited.get(), false, this->m_ref.n);
			for (index_t v=0; v < l; v++) 
				this->visited[this->current_path[v]] = true;
		}
	}
}