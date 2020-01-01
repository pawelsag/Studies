#pragma once
#include "internals.hpp"
#include "path_manager.hpp"
#include "utils.hpp"
#include <algorithm>
#include <cmath>

namespace TSP::GENETIC
{
	template<ANT_COLONY_ALG aca>
	class ant_colony
	{
		const matrix<tsp64_t>& m_ref;
		static constexpr int first_city_idx = 0;
		tsp64_t best_cost = std::numeric_limits<index_t>::max();
		static constexpr uint32_t MAX_ROUNDS_COUNT = 500;
		static constexpr double p = 0.5;
		static constexpr int alpha = 1;
		static constexpr int beta = 3; // 2 ... 5
		// for DAS algorithm
		double pheromone_density;
		// for CAS algorithm
		static constexpr int pehronom_n = MAX_ROUNDS_COUNT*0.05; 
		int is_ready_to_calc_pheromon = 0; 

		const int ant_count;
		// keep inforamtion about curently visited cities by ants
		// in given round
		// taking row means selecting ant,
		// taking col means selecting city 
		matrix<city_state> tabu;
		// tells about current pheromon density on each edge
		matrix<double> pheromone_lookup;
		std::vector<series_t> paths;

	public:
		ant_colony(const matrix<tsp64_t> &m)
		: m_ref(m),
		  ant_count(m.n),
		  tabu(m.n),	
		  pheromone_lookup(m.n)
		{
			auto greedy_path = path_manager::generate_gready_series(m_ref);
			pheromone_density =  double(ant_count)/path_manager::calculate_cost(greedy_path,m_ref);
			paths.resize(ant_count);
			for(int i =0 ; i < ant_count; i++)
				paths[i].resize(m.n);
			// set initial value for pheromon intesity lookup table
			pheromone_lookup.fill(pheromone_density); 
			tabu.fill(city_state::unvisited);
			this->solve();
		}
		
		void reset()
		{
			tabu.fill(city_state::unvisited);
			pheromone_lookup.fill(pheromone_density);
		}

		void solve()
		{
			bool ant_satisfied;
			tsp64_t current_best_val, best_city_idx;
			index_t from_city;
			for(uint32_t round =0 ; round < MAX_ROUNDS_COUNT; round++, is_ready_to_calc_pheromon++)
			{
				reset();
				init_paths();

				for(index_t next_city_idx =1; next_city_idx < m_ref.n ; next_city_idx++)
				{
					for(int ant = 0; ant < ant_count; ant++)
					{
						current_best_val = std::numeric_limits<index_t>::max();
						best_city_idx = 0;
						ant_satisfied = false;
						from_city = paths[ant][next_city_idx-1];

						for(index_t to_city =0; to_city < m_ref.n ; to_city++)
						{
							if(tabu.get_value(ant,to_city) == city_state::visited)
								continue;

							tsp64_t val = m_ref.get_value(from_city,to_city);
							if(current_best_val > val)
							{
								current_best_val = val;
								best_city_idx = to_city;
							}

							if(random(0.0, 1.0) < calc_probabilty(from_city, to_city, ant))
							{
								append_city(from_city, to_city, ant, next_city_idx);
								ant_satisfied = true;
								break;
							}
						}
						if(ant_satisfied == false)
						{
							append_city(from_city, best_city_idx, ant, next_city_idx);
						}
					}
				}
				get_best_value();
			}
		}

		void append_city(uint32_t from_city, uint32_t to_city, uint32_t ant, uint32_t next_city_idx)
		{
			if constexpr(aca == ANT_COLONY_ALG::CAS)
			{
				if(is_ready_to_calc_pheromon == pehronom_n)
				{
					pheromone_lookup.set_value(calc_pheromone_density(from_city,to_city,ant), from_city, to_city);
					is_ready_to_calc_pheromon =0;
				}
			}else{
			pheromone_lookup.set_value(calc_pheromone_density(from_city,to_city,ant), from_city, to_city);
			}
			
			paths[ant][next_city_idx] = to_city;
			tabu.set_value(visited, ant, to_city);
		}

		void get_best_value()
		{
			for(auto& path : paths)
			{
				tsp64_t cost = path_manager::calculate_cost(path,m_ref);
				if(best_cost > cost)
				{
					best_cost = cost;
				}
			}
		}

		void init_paths()
		{
			series_t cities = path_manager::generate_rand_series(m_ref.n);
			for(int i=0 ;i  < ant_count; i++)
			{
				paths[i][first_city_idx] = cities[i];
				tabu.set_value(visited, i, cities[i]);
			}
		}

		double calc_pheromone_density(uint32_t from_city, uint32_t to_city, uint32_t ant)
		{
			double accumulated_phermone =0.0;
			for(uint32_t ant = 0; ant < m_ref.n; ant++)
			{
				if constexpr (aca == ANT_COLONY_ALG::DAS)
				{
					if(tabu.get_value(ant,to_city) == city_state::visited)
						accumulated_phermone +=  pheromone_density;
				}else if constexpr (aca == ANT_COLONY_ALG::QAS)
				{
					if(tabu.get_value(ant,to_city) == city_state::visited)
						accumulated_phermone +=  pheromone_density/m_ref.get_value(from_city,to_city);
				}else
				{
					if(tabu.get_value(ant,to_city) == city_state::visited)
					{
						auto current_cost = path_manager::calculate_cost(paths[ant], this->m_ref);
						accumulated_phermone +=  pheromone_density/current_cost;
					}
				}
			}
			return p*pheromone_lookup.get_value(from_city,to_city) + accumulated_phermone; 
		}

		double calc_probabilty(uint32_t from_city, uint32_t to_city, uint32_t ant)
		{
			if( tabu.get_value(ant,to_city) == city_state::visited)
				return 0.0;

			double acc_sum =0.0;
			for(uint32_t city =0 ; city < m_ref.n; city++)
			{
				if(city != to_city && tabu.get_value(ant, city) == city_state::unvisited){
					auto val = pheromone_lookup.get_value(from_city,city);
					acc_sum+= std::pow(val,alpha)*std::pow(val,beta) ;
				}
			}

			double inverted_distacne = 1.0/m_ref.get_value(from_city,to_city);
			double pheromone = pheromone_lookup.get_value(from_city,to_city);

			if(acc_sum != 0.0)
				return std::pow(pheromone,alpha) * std::pow(inverted_distacne,beta) / acc_sum;
			else
				return 0.0;
		}		

		void show_results()
		{
			fmt::print("Best path :{}\n", this->best_cost);
		}
		
		tsp64_t get_result()
		{
			return this->best_cost;
		}

		~ant_colony()=default;
		
	};
}