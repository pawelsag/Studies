#pragma once
#include "internals.hpp"
#include "path_manager.hpp"
#include "utils.hpp"
#include <algorithm>

namespace TSP::GENETIC
{
	template<SELECTION_METHOD sm, CROSS_METHOD cm, MUTATION_METHOD mm>
	class genetic_algorithm
	{
		static constexpr uint32_t MAX_GENRATION_COUNT = 15000;
		static constexpr uint32_t MAX_POPULATION_SIZE = 1500;
		static constexpr uint32_t MAX_CHILDREN_SIZE = MAX_POPULATION_SIZE;

		// for tournament selection
		static constexpr uint32_t MAX_TOURNAMENT_GROUP_SIZE = MAX_POPULATION_SIZE * 0.2;
		// for rank selection
		static constexpr uint32_t RANK_TRESHOLD = MAX_POPULATION_SIZE * 0.95;
		
		static constexpr float MUTATION_PROBABILITY = 0.1;
		static constexpr float CROSS_PROBABILITY = 0.8;
		
		using population_t = std::vector<individual>;
		
		const matrix<tsp64_t>& m_ref;
		population_t population;
		population_t children;
		index_t next_child_id =0;
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
			children.resize(MAX_CHILDREN_SIZE);

			generate_population();
			this->solve();
		}

		void show_results()
		{
			fmt::print("Best path :{}\n", this->best_cost);
		}
		tsp64_t get_result()
		{
			return this->best_cost;
		}

		void PMX_cross(series_t &p1_tmp, series_t &p2_tmp)
		{
			constexpr index_t max_val = std::numeric_limits<index_t>::max();
			auto k1 =random(0u, this->m_ref.n-1);
			auto k2 =random(0u, this->m_ref.n-1);
			
			if(k1 > k2) std::swap(k1,k2);
			
			//this will limit maximum size of our solution;
			std::fill(city_link_p1.begin(),city_link_p1.end(), max_val);
			std::fill(city_link_p2.begin(),city_link_p2.end(), max_val);
			children[next_child_id  ].path = p1_tmp;
			children[next_child_id+1].path = p2_tmp;
			auto& p1 = children[next_child_id  ].path; 
			auto& p2 = children[next_child_id+1].path;

			for(tsp64_t i = k1; i < k2; i++){
				std::swap(p1[i], p2[i]);
				city_link_p1[p1[i]] = p2[i];
				city_link_p2[p2[i]] = p1[i];
			}

			for(tsp64_t i = 0; i < k1; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]];
				if( v != max_val)
				{
					// max 2 jumps
					while(city_link_p1[v] != max_val)
					{
						v = city_link_p1[v];
					}
					p1[i]= v;		
				}

				v = city_link_p2[p2[i]];
				if( v != max_val){
					// max 2 jumps
					while(city_link_p2[v] != max_val)
					{
						v = city_link_p2[v];
					}
					p2[i] = v;		
				}
			}

			for(tsp64_t i = k2;i < this->m_ref.n; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]];
				if( v != max_val){
					// max 2 jumps
					while(city_link_p1[v] != max_val)
					{
						v = city_link_p1[v];
					}
					p1[i]=  v;		
				}
				
				v = city_link_p2[p2[i]];
				if( v != max_val){
					// max 2 jumps
					while(city_link_p2[v] != max_val)
					{
						v = city_link_p2[v];
					}
					p2[i]= v;
				}
			}
		}

		void OX_cross(series_t & p1_tmp, series_t & p2_tmp)
		{
			auto k1 =random(0u, this->m_ref.n-1);
			auto k2 =random(0u, this->m_ref.n-1);
			children[next_child_id  ].path = p1_tmp;
			children[next_child_id+1].path = p2_tmp;

			auto& p1 = children[next_child_id  ].path; 
			auto& p2 = children[next_child_id+1].path;

			std::fill(is_visted_p1.begin(),is_visted_p1.end(), false);
			std::fill(is_visted_p2.begin(),is_visted_p2.end(), false);

			if(k1 > k2) std::swap(k1,k2);

			for(tsp64_t i = k1; i < k2; i++)
			{
				is_visted_p1[p1[i]] = true;
				is_visted_p2[p2[i]] = true;
				std::swap(p1[i], p2[i]);
			}

			tsp64_t p1_k =k2, p2_k =k2;
			for(tsp64_t i = k2; i < this->m_ref.n; i++)
			{
				if( is_visted_p2[p1_tmp[i]] == false){
					p1[p1_k++] = p1_tmp[i];
				}
				if( is_visted_p1[p2_tmp[i]] == false){
					p2[p2_k++] = p2_tmp[i];
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
					if(p2_k == this->m_ref.n)
						p2_k=0;

					p2[p2_k++] = p2_tmp[i];
				}
			}

			for(tsp64_t i = k1; i < k2; i++)
			{
				if( is_visted_p2[p1_tmp[i]] == false ){
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

		void tournament_selection()
		{
			population_t tournament_group;
			tournament_group.reserve(MAX_TOURNAMENT_GROUP_SIZE);

			for(tsp64_t g =0 ; g < MAX_POPULATION_SIZE; g++)
			{
				//select tournament group
				for(tsp64_t j =0 ; j < MAX_TOURNAMENT_GROUP_SIZE; j++)
				{
					tournament_group.push_back(children[random(0u, next_child_id-1)]);
				}
				// get smallest elelment
				population[g] = (*(std::min_element(tournament_group.begin(),tournament_group.end())));
				tournament_group.clear();
			}
		}
		
		void rank_selection()
		{
			std::sort(children.begin(), children.end(), std::less<individual>());
			auto childs_to_copy = next_child_id < RANK_TRESHOLD ? next_child_id : RANK_TRESHOLD; 
			// fill redundant population with paths from correct scope
			for(tsp64_t g = 0; g < MAX_POPULATION_SIZE; g++)
			{	if(g < childs_to_copy){
					population[g] = children[g];
				}else
					population[g] = children[random(0u,childs_to_copy-1)];
			}
		}

		void generate_population()
		{
			for(tsp64_t i = 0 ; i < MAX_POPULATION_SIZE; i++)
			{
				population[i].path = path_manager::generate_rand_series(this->m_ref.n);
				population[i].cost = path_manager::calculate_cost(population[i].path, this->m_ref);
			}
		}
		void append_ellite()
		{
			std::sort(population.begin(), population.end(), std::less<individual>());
			uint32_t k =0;
			for(uint32_t i = next_child_id; i < MAX_CHILDREN_SIZE; i++)
			{	
				children[i] = population[k++];
			}
		}

		void solve()
		{
			tsp64_t generation = 0;
			tsp64_t tmp_cost;

			while(generation < MAX_GENRATION_COUNT)
			{
				for(uint32_t i =0 ; i < MAX_CHILDREN_SIZE*0.5-1; i++)
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

						if(random(0.0, 1.0) < MUTATION_PROBABILITY)
						{
							auto v1 =random(0u, this->m_ref.n-1);
							auto v2 =random(0u, this->m_ref.n-1);
							if constexpr(mm == MUTATION_METHOD::INSERTION){
								insertion(this->children[next_child_id].path,   v1,v2);
								insertion(this->children[next_child_id+1].path, v1,v2);
							}else if constexpr(mm == MUTATION_METHOD::INVERTION){
								invertion(this->children[next_child_id].path,   v1,v2);
								invertion(this->children[next_child_id+1].path, v1,v2);
							}else{
								displacement(this->children[next_child_id].path,   v1,v2);
								displacement(this->children[next_child_id+1].path, v1,v2);

							}
						}

						children[next_child_id  ].cost = path_manager::calculate_cost(this->children[next_child_id  ].path, this->m_ref);
						children[next_child_id+1].cost = path_manager::calculate_cost(this->children[next_child_id+1].path, this->m_ref);
						next_child_id += 2;
					}
				}

				append_ellite();
				if constexpr(sm == SELECTION_METHOD::TOURNAMENT){
					tournament_selection();
				}else{
					rank_selection();
				}

				tmp_cost = std::min_element(population.begin(),population.end())->cost;

				if(best_cost > tmp_cost)
				{
					best_cost = tmp_cost;
				}
				next_child_id =0;
				generation++;
			}
		}
		~genetic_algorithm() = default;		
	};


}