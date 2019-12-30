#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <map>

namespace TSP {

using tsp64_t = int64_t;
using index_t = uint32_t;
using series_t = std::vector<index_t>;
using directory_info_t = std::vector<std::string>;
using tsp_results_t = std::map<std::string, tsp64_t>;

struct point
{
  tsp64_t p1, p2;
};

using path_t = std::vector<point>;
	
	namespace STOCHASTICS{

		enum class START_PATH_TYPE
		{
			NATURAL,
			RANDOM,
			APROX
		};
		
		enum class COOLING_METHOD
		{
			LINEAR,
			GEOMETRIC,
			LOGARITHM
		};

		enum class ADJ_ALGORITHM
		{
			SWAP,
			INSERT,
			INVERT
		};
	}
	namespace GENETIC
	{
		enum class SELECTION_METHOD{
			TOURNAMENT,
			RANK,
		};

		enum class CROSS_METHOD{
			PMX,
			OX
		};

		enum class MUTATION_METHOD{
			INSERTION,
			INVERTION,
			DISPLACEMENT
		};

		struct individual
		{
			series_t path;
			tsp64_t cost;

			void show()
			{
				fmt::print("cost :{}\n", cost);
			}

			bool operator<(const individual &a)
			{
				return this->cost < a.cost;
			}

			friend bool operator<(const individual &a, const individual &b);
		};

	}

}