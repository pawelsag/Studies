#pragma once

#include <functional>
#include <vector>

#include "utils.hpp"
#include "precise_algorithms.hpp"
#include "path_manager.hpp"

namespace TSP::STOCHASTICS
{
	struct tabu_t
	{
		tsp64_t v;
		tsp64_t penalty;
	};

	template <START_PATH_TYPE SP, ADJ_ALGORITHM AA>
	class tabu_search
	{	
		std::vector<tabu_t> tabu_list;
		const matrix<tsp64_t>& m_ref;
		tsp64_t current_cost = 0;
		tsp64_t best_cost = 0;
		series_t current_path;
		series_t best_path;

		tsp64_t without_better_solutions ;
		tsp64_t max_lack_of_solutions;

		static constexpr tsp64_t penalty = 5;
		static constexpr tsp64_t max_loop_count = 10'000;
		
	public:
		tabu_search(const matrix<tsp64_t> &m)
		: m_ref(m)

		{
			if constexpr (SP == START_PATH_TYPE::NATURAL)
			{
				current_path = path_manager::generate_natural_series(m_ref.n);
			}else if constexpr (SP == START_PATH_TYPE::RANDOM)
			{
				current_path = path_manager::generate_rand_series(m_ref.n);
			}else
			{
				current_path = path_manager::generate_gready_series(m_ref);
			}
			tabu_list.resize(m_ref.n * m_ref.n);
			max_lack_of_solutions = max_loop_count * 0.05;
			this->solve();

		}
		void show_results()
		{
			fmt::print( "{} \n", this->best_cost );
			path_manager::show( this->best_path );
		}

		tsp64_t get_result()
		{
			return this->best_cost;
		}

		void adj_swap(tsp64_t p1, tsp64_t p2)
		{	
			std::swap(current_path[p1], current_path[p2]);
		}

		void adj_insert(tsp64_t p1, tsp64_t p2)
		{
			if (p1 < p2){
				// remeber value which will be inserted
				auto tmp = current_path[p2];
				// move all values to the right
				while(p1 < p2){
					current_path[p2] = current_path[p2-1];
					p2--; 
				} 
				current_path[p1+1] = tmp;
			}else
			{
				// remeber value which will be inserted
				auto tmp = current_path[p2];
				// move all values to the right
				while(p1 > p2)
				{
					current_path[p2] = current_path[p2+1];
					p2++; 
				}
				current_path[p1] = tmp;
			}
		}

		void adj_invert(tsp64_t p1, tsp64_t p2)
		{
			// make sure that p2 is allways bigger
			if (p1 > p2) std::swap(p1,p2);
			TSP::reverse(&current_path[p1], &current_path[p2]);
		}
		
		void decrement_tabu()
		{
			for(auto beg = this->tabu_list.begin(); beg != this->tabu_list.end(); beg++)
				if(beg->penalty > 0) beg->penalty--;
		}

		tsp64_t tabu_penalty(tsp64_t p1, tsp64_t p2)
		{

			tsp64_t vertex = p1*this->m_ref.n + p2;

			auto val = this->tabu_list.begin() + vertex;
			val->penalty += penalty;
			return (penalty/val->penalty) *this->current_cost;

		}
		
		tsp64_t calculate_swap_cost(tsp64_t p1,
									 tsp64_t p2)
		{
			tsp64_t current_cost_copy;
	     	
	     	this->adj_swap(p1, p2);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
	        this->adj_swap(p1, p2);
	        return current_cost_copy;
		}

		tsp64_t calculate_insert_cost(tsp64_t p1,
									 tsp64_t p2)
		{
			tsp64_t current_cost_copy;
	     	this->adj_insert(p1, p2);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
	     	this->adj_insert(p2, p1+1);

	        return current_cost_copy;
		}

		tsp64_t calculate_invert_cost(tsp64_t p1,
							 		  tsp64_t p2)
		{
			tsp64_t current_cost_copy;

	     	this->adj_invert(p1, p2);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
			this->adj_invert(p1, p2);
			   
	        return current_cost_copy;
		}

		void reset()
		{
			this->current_cost = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
		}
		
		void solve()
		{

		    this->reset();		    
		    this->best_cost = this->current_cost;
		    this->best_path = this->current_path; 
		    tsp64_t loop_i = 0; 

		    while (loop_i < max_loop_count)
		    {
		        tsp64_t new_cost = std::numeric_limits<tsp64_t>::max();
				tsp64_t p1,p2;
				for(tsp64_t i =0 ; i < this->m_ref.n; i++)
				{
					for(tsp64_t j = i+1 ; j < this->m_ref.n; j++)
					{
						tsp64_t cost;
						if constexpr (AA == ADJ_ALGORITHM::SWAP)
						{
							cost = this->calculate_swap_cost(i,j);
						}else if constexpr (AA == ADJ_ALGORITHM::INSERT)
						{
							cost = this->calculate_insert_cost(i,j);
						}else{
							cost = this->calculate_invert_cost(i,j);
						}

						if( new_cost > cost + tabu_penalty(i,j))
						{
							new_cost = cost;
							p1 = i;
							p2 = j;
						}
					}
				}
				this->decrement_tabu();

				without_better_solutions++;

				if(current_cost > new_cost){
					without_better_solutions = 0;
				}

				if constexpr (AA == ADJ_ALGORITHM::SWAP)
				{
					this->tabu_search::adj_swap(p1,p2);
				}else if constexpr (AA == ADJ_ALGORITHM::INSERT)
				{
					this->tabu_search::adj_insert(p1,p2);
				}else{
					this->tabu_search::adj_invert(p1,p2);
				}

				current_cost = new_cost;

		        if(this->current_cost < this->best_cost)
		        {							
		        	this->best_cost = this->current_cost;
		        	this->best_path = this->current_path;
		        }

		        // critical event
				if( without_better_solutions > max_lack_of_solutions)
				{
					current_path = path_manager::generate_rand_series(m_ref.n);
					this->reset();
				}
				loop_i++;
		    }
		}
	};
}	