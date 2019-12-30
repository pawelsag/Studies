#pragma once
#include "internals.hpp"
#include "path_manager.hpp"
#include "utils.hpp"
#include <algorithm>

namespace TSP::GENETIC
{
	bool operator<(const individual &a, const individual &b)
	{
		return a.cost < b.cost;
	}

	template<SELECTION_METHOD sm, CROSS_METHOD cm, MUTATION_METHOD mm>
	class genetic_algorithm
	{
		static constexpr uint32_t MAX_GENRATION_COUNT = 10000;
		static constexpr uint32_t MAX_POPULATION_SIZE = 300;
		static constexpr uint32_t MAX_CHILDREN_SIZE = MAX_POPULATION_SIZE;

		// only when tournament selection is selected
		static constexpr uint32_t MAX_TOURNAMENT_GROUP_SIZE = MAX_POPULATION_SIZE * 0.2;
		static constexpr uint32_t RANK_TRESHOLD = MAX_POPULATION_SIZE * 0.90;
		static constexpr float MUTATION_PROBABILITY = 0.05;
		static constexpr float CROSS_PROBABILITY = 0.6;
		
		using population_t = std::vector<individual>;
		
		const matrix<tsp64_t>& m_ref;
		population_t population;

		// for pmx cross
		series_t city_link_p1, city_link_p2;
		// for ox cross 
		std::vector<bool> is_visted_p1, is_visted_p2;

		tsp64_t best_cost = std::numeric_limits<index_t>::max();

	public:
		genetic_algorithm(const matrix<tsp64_t> &m)
		: m_ref(m)
		{
			if constexpr(cm == CROSS_METHOD::PMX){
				city_link_p1.resize(this->m_ref.n);
				city_link_p2.resize(this->m_ref.n);
			}else{
				is_visted_p1.resize(this->m_ref.n);
				is_visted_p2.resize(this->m_ref.n);
			}

			population.resize(MAX_POPULATION_SIZE);
			generate_population();
			this->solve();
		}
		void show_results()
		{
			fmt::print("Best path :{}", this->best_cost);
		}

		void PMX_cross(series_t &p1, series_t &p2)
		{
			constexpr index_t max_val = std::numeric_limits<index_t>::max();
			auto k1 =random(0u, this->m_ref.n-1);
			auto k2 =random(0u, this->m_ref.n-1);
			
			if(k1 > k2) std::swap(k1,k2);
			
			// this will limit maximum size of our solution;
			std::fill(city_link_p1.begin(),city_link_p1.end(), max_val);
			std::fill(city_link_p2.begin(),city_link_p2.end(), max_val);

			for(tsp64_t i = k1; i < k2; i++){
				std::swap(p1[i], p2[i]);
				city_link_p1[p1[i]] = p2[i];
				city_link_p2[p2[i]] = p1[i];
			}

			for(tsp64_t i = 0; i < k1; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p1[v] != max_val)
					{
						v = city_link_p1[v];
					}
					p1[i]= v;		
				}

				v = city_link_p2[p2[i]];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p2[v] != max_val)
					{
						v = city_link_p2[v];
					}
					p2[i]= v;		
				}
			}

			for(tsp64_t i = k2; i < this->m_ref.n; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p1[v] != max_val)
					{
						v = city_link_p1[v];
					}
					p1[i]=  v;		
				}
				
				v = city_link_p2[p2[i]];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p2[v] != max_val)
					{
						v = city_link_p2[v];
					}
					p2[i]= v;
				}
			}
		}

		void OX_cross(series_t & p1, series_t & p2)
		{
			auto k1 =random(0u, this->m_ref.n-1);
			auto k2 =random(0u, this->m_ref.n-1);
			series_t p1_tmp = p1, p2_tmp =p2;
			std::fill(is_visted_p1.begin(),is_visted_p1.end(), false);
			std::fill(is_visted_p1.begin(),is_visted_p1.end(), false);

			if(k1 > k2) std::swap(k1,k2);

			for(tsp64_t i = k1; i < k2; i++)
			{
				is_visted_p1[p1[i]] = true;
				is_visted_p2[p2[i]] = true;
				std::swap(p1[i], p2[i]);
			}

			for(tsp64_t i = 0; i < k2-k1; i++)
			{
				p1[i] = p1_tmp[k1 + i];
				p2[i] = p2_tmp[k1 + i];
			}

			tsp64_t p1_k =k2, p2_k =k2;
			for(tsp64_t i = 0; i < this->m_ref.n - k2; i++)
			{
				if( is_visted_p2[p1_tmp[k2 + i]] == false){
					p1[p1_k++] = p1_tmp[k2 + i];
				}
				if( is_visted_p1[p2_tmp[k2 + i]] == false){
					p2[p2_k++] = p2_tmp[k2 + i];
				}
			}
	
			for(tsp64_t i = 0; i < k1; i++)
			{
				if( is_visted_p2[p1_tmp[i]] == false){
					if(p1_k == this->m_ref.n)
						p1_k =0;
					p1[p1_k++] = p1_tmp[i];
				}
				
				if( is_visted_p1[p2_tmp[i]] == false){
					if(p2_k >= this->m_ref.n)
						p2_k=0;

					p2[p2_k++] = p2_tmp[i];
				}
			}
		}

		void insertion(series_t & path, index_t v1, index_t v2)
		{
			if (v1 < v2){
				// remeber value which will be inserted
				auto tmp = path[v2];
				// move all values to the right
				while(v1 < v2){
					path[v2] = path[v2-1];
					v2--; 
				} 
				path[v1+1] = tmp;
			}else
			{
				// remeber value which will be inserted
				auto tmp = path[v2];
				// move all values to the right
				while(v1 > v2)
				{
					path[v2] = path[v2+1];
					v2++; 
				}
				path[v1] = tmp;
			}
		}

		void invertion(series_t & path, index_t v1, index_t v2)
		{
			if (v1 > v2) std::swap(v1,v2);
			TSP::reverse(&path[v1], &path[v2]);
		}

		void displacement(series_t & path, index_t v1, index_t v2)
		{
			std::swap(path[v1], path[v2]);
		}

		population_t tournament_selection()
		{
			population_t tournament_group;
			tournament_group.reserve(MAX_TOURNAMENT_GROUP_SIZE);

			population_t selection_res;
			selection_res.reserve(MAX_POPULATION_SIZE);

			for(tsp64_t g =0 ; g < MAX_POPULATION_SIZE; g++)
			{
				//select tournament group
				for(tsp64_t j =0 ; j < MAX_TOURNAMENT_GROUP_SIZE; j++)
				{
					tournament_group.push_back(population[random(0u, MAX_POPULATION_SIZE-1)]);
				}

				// get smallest elelment
				selection_res.push_back(*(std::min_element(tournament_group.begin(),tournament_group.end())));
				tournament_group.clear();

			}
			return selection_res;
		}
		
		population_t rank_selection()
		{
			population_t selection_res = population; 
			std::sort(selection_res.begin(), selection_res.end(), std::less<individual>());
			// fill redundant population with paths from correct scope
			for(tsp64_t g = RANK_TRESHOLD; g < MAX_POPULATION_SIZE; g++)
			{	
				selection_res[g] = selection_res[random(0u,RANK_TRESHOLD-1)];
			}
			return selection_res;
		}

		void generate_population()
		{
			for(tsp64_t i = 0 ; i < MAX_POPULATION_SIZE; i++)
			{
				population[i].path = path_manager::generate_rand_series(this->m_ref.n);
				population[i].cost = path_manager::calculate_cost(population[i].path, this->m_ref);
			}
		}

		void solve()
		{
			tsp64_t generation = 0;
			tsp64_t tmp_cost;

			while(generation < MAX_GENRATION_COUNT)
			{
				for(uint32_t i =0 ; i < MAX_CHILDREN_SIZE; i++)
				{
					if(random(0.0, 1.0) < CROSS_PROBABILITY)
					{
						auto k1 =random(0u, MAX_POPULATION_SIZE-1);
						auto k2 =random(0u, MAX_POPULATION_SIZE-1);
						if constexpr(cm == CROSS_METHOD::PMX){
							PMX_cross(this->population[k1].path,this->population[k2].path);
						}else{
							OX_cross(this->population[k1].path,this->population[k2].path);
						}

						population[k1].cost = path_manager::calculate_cost(population[k1].path, this->m_ref);
						population[k2].cost = path_manager::calculate_cost(population[k2].path, this->m_ref);
					}

					if(random(0.0, 1.0) < MUTATION_PROBABILITY)
					{
						auto k1 =random(0u, MAX_POPULATION_SIZE-1);
						auto v1 =random(0u, this->m_ref.n-1);
						auto v2 =random(0u, this->m_ref.n-1);
						if constexpr(mm == MUTATION_METHOD::INSERTION){
							insertion(this->population[k1].path,v1,v2);
						}else if constexpr(mm == MUTATION_METHOD::INVERTION){
							invertion(this->population[k1].path,v1,v2);
						}else{
							displacement(this->population[k1].path,v1,v2);
						}

						population[k1].cost = path_manager::calculate_cost(population[k1].path, this->m_ref);
					}
				}	
				tmp_cost = std::min_element(population.begin(),population.end())->cost;
				if(best_cost > tmp_cost)
				{
					best_cost = tmp_cost;	
				}
				
				if constexpr(sm == SELECTION_METHOD::TOURNAMENT){
					tournament_selection();
				}else{
					rank_selection();
				}
				generation++;
			}
		}
		~genetic_algorithm() = default;		
	};


}