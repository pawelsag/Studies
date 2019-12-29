#pragma once
#include "internals.hpp"
#include "path_manager.hpp"
#include "utils.hpp"
#include <algorithm>

namespace TSP::GENETIC
{
	enum class SELECTION_METHOD{
		TOURNAMENT,
		RANK,
	};
	struct individual
	{
		series_t path;
		tsp64_t cost;
		double fitness;
		void show()
		{
			fmt::print("cost :{}  fitness :{}\n", cost,fitness);
		}

		bool operator<(const individual &a)
		{
			return this->cost < a.cost;
		}

		friend bool operator<(const individual &a, const individual &b);
	};

	bool operator<(const individual &a, const individual &b)
	{
		return a.cost < b.cost;
	}

	template<SELECTION_METHOD sm>
	class genetic_algorithm
	{
		static constexpr tsp64_t MAX_GENRATION_COUNT = 100;
		static constexpr tsp64_t MAX_POPULATION_SIZE = 50;

		// only when tournament selection is selected
		static constexpr tsp64_t MAX_TOURNAMENT_GROUP_SIZE = MAX_POPULATION_SIZE * 0.2;
		static constexpr uint32_t RANK_TRESHOLD = MAX_POPULATION_SIZE * 0.90;
		
		using population_t = std::vector<individual>;
		
		const matrix<tsp64_t>& m_ref;
		population_t population;	
		series_t city_link_p1, city_link_p2;

	public:
		genetic_algorithm(const matrix<tsp64_t> &m)
		: m_ref(m)
		{
			population.resize(MAX_POPULATION_SIZE);
			generate_population();

			tournament_selection();
			city_link_p1.resize(9);
			city_link_p2.resize(9);
			rank_selection();
			this->solve();
		}

		void PMX_cross(series_t &p1, series_t &p2)
		{
			constexpr index_t max_val = std::numeric_limits<index_t>::max();
			auto k1 =random(0u, this->m_ref.n);
			auto k2 =random(0u, this->m_ref.n);
			
			if(k1 > k2) std::swap(k1,k2);
			
			// this will limit maximum size of our solution;
			std::fill(city_link_p1.begin(),city_link_p1.end(), max_val);
			std::fill(city_link_p2.begin(),city_link_p2.end(), max_val);

			for(tsp64_t i = k1; i < k2; i++){
				std::swap(p1[i], p2[i]);
				city_link_p1[p1[i]-1] = p2[i];
				city_link_p2[p2[i]-1] = p1[i];
			}

			for(tsp64_t i = 0; i < k1; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]-1];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p1[v-1] != max_val)
					{
						v = city_link_p1[v-1];
					}
					p1[i]= v;		
				}

				v = city_link_p2[p2[i]-1];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p2[v-1] != max_val)
					{
						v = city_link_p2[v-1];
					}
					p2[i]= v;		
				}
			}

			for(tsp64_t i = k2; i < this->m_ref.n; i++)
			{ 
				tsp64_t v = city_link_p1[p1[i]-1];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p1[v-1] != max_val)
					{
						v = city_link_p1[v];
					}
					p1[i]=  v;		
				}
				
				v = city_link_p2[p2[i]-1];
				if( v != max_val){
					// max 2 jumps
					if(city_link_p2[v-1] != max_val)
					{
						v = city_link_p2[v-1];
					}
					p2[i]= v;
				}
			}
		}

		void OX_cross(series_t & p1, series_t & p2)
		{

		}

		void EX_cross(series_t & p1, series_t & p2)
		{

		}

		void mutate(series_t & p1)
		{

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
					tournament_group.push_back(population[random(0u, this->m_ref.n)]);
				}

				// get smallest elelment
				selection_res.push_back(*(std::min_element(tournament_group.begin(),tournament_group.begin() +MAX_TOURNAMENT_GROUP_SIZE )));
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
				selection_res[g] = selection_res[random(0u,RANK_TRESHOLD)];
			}
			return selection_res;
		}

		void generate_population()
		{
			for(tsp64_t i = 0 ; i < MAX_POPULATION_SIZE; i++)
			{
				population[i].path = path_manager::generate_rand_series(this->m_ref.n);
				population[i].cost = path_manager::calculate_cost(population[i].path, this->m_ref);
				population[i].fitness = 1.0/population[i].cost;
			}
		}

		void solve()
		{
			tsp64_t generation = 0;
			while(generation < MAX_GENRATION_COUNT)
			{
				generation++;
			}

		}

		~genetic_algorithm() = default;

	private:
		
	};
}