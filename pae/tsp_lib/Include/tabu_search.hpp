#pragma once

#include <functional>
#include <list>

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


		std::list<tabu_t> tabu_list;
		const matrix<tsp64_t>& m_ref;
		tsp64_t current_cost = 0;
		tsp64_t best_cost = 0;
		series_t current_path;
		series_t copy_path;
		series_t best_path;

		tsp64_t without_better_solutions =0;
		tsp64_t max_lack_of_solutions;
		// tsp64_t reset_treshold;

		static constexpr tsp64_t penalty = 10;
		static constexpr tsp64_t max_loop_count = 10'000;
		
	public:
		tabu_search(const matrix<tsp64_t> &m)
		: m_ref(m)
		{
			std::function<void(tsp64_t,tsp64_t)> shuffel_method;
			std::function<tsp64_t(tsp64_t,tsp64_t)> cost_method;

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

			if constexpr (AA == ADJ_ALGORITHM::SWAP)
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_swap(p1,p2);};
				cost_method = [this](tsp64_t p1, tsp64_t p2){ return this->calculate_swap_cost(p1,p2);};
			}else if constexpr (AA == ADJ_ALGORITHM::INSERT)
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_insert(p1,p2);};
				cost_method = [this](tsp64_t p1, tsp64_t p2){ return this->calculate_insert_cost(p1,p2);};
			}else
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_invert(p1,p2);};
				cost_method = [this](tsp64_t p1, tsp64_t p2){ return this->calculate_invert_cost(p1,p2);};
			}
			max_lack_of_solutions = max_loop_count * 0.1;
			// reset_treshold = max_loop_count * 0.70;
			this->solve(shuffel_method,cost_method);

		}
		void show_results()
		{
			fmt::print("{} \n", this->best_cost);
			for(int i =0 ; i < m_ref.n; i++)
				fmt::print("{}, ", best_path[i]);
			fmt::print("\n");
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
				else beg = this->tabu_list.erase(beg);
		}

		tsp64_t tabu_penalty(tsp64_t p1, tsp64_t p2)
		{

			tsp64_t vertex = p1*this->m_ref.n + p2;

			std::list<tabu_t>::iterator val = std::find_if(this->tabu_list.begin(), 
								  this->tabu_list.end(), 
								  [vertex](tabu_t &a){
								  	return a.v == vertex; 
								  });

			if( val != this->tabu_list.end() )
				return val->penalty*100;

			this->tabu_list.push_back({vertex, penalty});
			return 0;
		}
		
		tsp64_t calculate_swap_cost(tsp64_t p1,
									 tsp64_t p2)
		{
			tsp64_t current_cost_copy;
	     	
	     	this->adj_swap(this->current_path[p1], this->current_path[p2]);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
	        this->adj_swap(this->current_path[p1], this->current_path[p2]);
	        return current_cost_copy;
		}

		tsp64_t calculate_insert_cost(tsp64_t p1,
									 tsp64_t p2)
		{
			tsp64_t current_cost_copy;
	     	this->adj_insert(this->current_path[p1], this->current_path[p2]);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
	     	this->adj_insert(this->current_path[p2], this->current_path[p1+1]);

	        return current_cost_copy;
		}

		tsp64_t calculate_invert_cost(tsp64_t p1,
							 		  tsp64_t p2)
		{
			tsp64_t current_cost_copy;

	     	this->adj_invert(this->current_path[p1], this->current_path[p2]);
	     	current_cost_copy = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
			this->adj_invert(this->current_path[p1], this->current_path[p2]);
			   
	        return current_cost_copy;
		}

		void reset()
		{
			this->current_cost = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
		    this->copy_path = this->current_path;
		}

		void solve(std::function<void(tsp64_t,tsp64_t)> &shuffle,
				   std::function<tsp64_t(tsp64_t,tsp64_t)> &calc_cost)
		{

		    this->reset();
		    this->best_cost = this->current_cost;
		    this->best_path =this->current_path; 
		    tsp64_t loop_i = 0; 

		    while (loop_i < max_loop_count)
		    {
		        tsp64_t lower_cost = std::numeric_limits<tsp64_t>::max();
				tsp64_t p1,p2;
				for(int i =0 ; i < this->m_ref.n; i++)
				{
					for(int j = i+1 ; j < this->m_ref.n; j++)
					{
						auto cost = calc_cost(i, j);
						if(lower_cost > cost + tabu_penalty(i,j))
						{
							lower_cost = cost;
							p1 = i;
							p2 = j;
						}
					}
				}
				shuffle(p1,p2);
	            current_cost = lower_cost;

				this->decrement_tabu();

				without_better_solutions++;
				loop_i++;

		        if(this->current_cost < this->best_cost)
		        {
		        	without_better_solutions = 0;
		        	this->best_cost = this->current_cost;
		        	this->best_path = this->current_path;
		        }

		        // critical event
				if( without_better_solutions > max_lack_of_solutions){
					current_path = path_manager::generate_rand_series(m_ref.n);
					this->reset();
				}
		    }
		}
	};
}	