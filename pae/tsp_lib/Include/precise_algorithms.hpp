#pragma once
#include "internals.hpp"
#include <memory>
#include <cstring>

namespace TSP::PRECISE{

	tsp64_t brutforce(const matrix<tsp64_t>& M);

	
	class branch_and_bound{
		const matrix<tsp64_t>& m_ref;
		std::unique_ptr<bool[]> visited;
		std::unique_ptr<index_t[]> current_path;
		// alias for upper_bound
		tsp64_t final_cost = std::numeric_limits<tsp64_t>::max();
		tsp64_t current_cost = 0;

	public:

		branch_and_bound(const matrix<tsp64_t> &m)
		: m_ref(m),
		  visited(std::make_unique<bool[]>(m_ref.n)),
		  current_path(std::make_unique<index_t[]>(m_ref.n))
		{
			std::memset(this->current_path.get(), -1, this->m_ref.n);
			std::memset(this->visited.get(), false, this->m_ref.n);

			visited[0] = true;
			this->current_path[0] = 0;
			this->solve(1);
		}
		
		void show_results()
		{
			fmt::print("MIN COST : {}\n", this->final_cost);
		}

		tsp64_t get_result()
		{
			return final_cost;
		}

	private:
		inline tsp64_t 
		calculate_lower_bound(index_t index)
		{	
			tsp64_t	val =0;
			for(index_t i = index ; i < this->m_ref.n; i++)
				val += this->min(i);
			return val;
		}	

		inline tsp64_t 
		min(index_t v1){
			tsp64_t min = std::numeric_limits<tsp64_t>::max();

			for (index_t v2 = 0; v2 < this->m_ref.n; v2++){ 
				auto val = this->m_ref.get_value(v1,v2);
				if ( val < min && v1 != v2)
					min = val;
			}

			return min;
		}

		void solve(index_t level);
	};

};