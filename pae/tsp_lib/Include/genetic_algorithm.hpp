#pragma once
#include "internals.hpp"
#include "path_manager.hpp"
#include "utils.hpp"

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
	};

	template<SELECTION_METHOD sm>
	class genetic_algorithm
	{
		const matrix<tsp64_t>& m_ref;
		std::vector<individual> population;

		static constexpr tsp64_t MAX_GENRATION_COUNT = 100;
		static constexpr tsp64_t MAX_population_SIZE = 50;

		// only when tournament selection is selected
		static constexpr tsp64_t MAX_TOURNAMENT_GROUP_SIZE = MAX_population_SIZE * 0.2;

	public:
		genetic_algorithm(const matrix<tsp64_t> &m)
		: m_ref(m)
		{
			population.resize(MAX_population_SIZE);
			generate_population();

			this->solve();
		}

		void crossover(series_t & p1, series_t & p2)
		{

		}

		void mutate(series_t & p1)
		{

		}
		
		void generate_population()
		{
			for(tsp64_t i =0 ; i < MAX_population_SIZE;i++)
			{
				population[i].path = path_manager::generate_rand_series(m_ref.n);
				population[i].cost = path_manager::calculate_cost(population[i].path, this->m_ref);
				path_manager::show(population[i].path);
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