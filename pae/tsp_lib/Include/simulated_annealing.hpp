#include <cmath>
#include <chrono>
#include <functional>

#include "utils.hpp"
#include "precise_algorithms.hpp"
#include "path_manager.hpp"
constexpr const char * common_header = "file_name;data_size;time";

namespace TSP::STOCHASTICS
{	
	using chrono_time_point = std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::duration<long int, std::ratio<1, 1000000000>>>;
	
	template <START_PATH_TYPE SP, COOLING_METHOD CM, ADJ_ALGORITHM AA>
	class simmulated_annealing
	{
		const matrix<tsp64_t>& m_ref;
		tsp64_t best_cost = std::numeric_limits<tsp64_t>::max();
		tsp64_t current_cost = 0;
		series_t current_path;
		series_t best_path;
		chrono_time_point ref_time;
		chrono_time_point current_time;
		std::chrono::duration<double> diff;

		static constexpr double begin_temperature = 100'00.0;
	    static constexpr double final_temperature = 0.00001;
	    static constexpr double cooling_rate = 0.95;

		double temperature = begin_temperature;
		double time =0.0;

	public:
		
		simmulated_annealing(const matrix<tsp64_t> &m)
		: m_ref(m)
		{
			std::function<void(void)> cooling_method;
			std::function<void(tsp64_t,tsp64_t)> shuffel_method;

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

			if constexpr (CM == COOLING_METHOD::LINEAR)
			{
				cooling_method = [this](){ this->linear_cooling();};
			}else if constexpr (CM == COOLING_METHOD::GEOMETRIC)
			{
				cooling_method = [this](){ this->geometric_cooling();};
			}else
			{
				cooling_method = [this](){ this->logarithm_cooling();};
			}

			if constexpr (AA == ADJ_ALGORITHM::SWAP)
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_swap(p1,p2);};
			}else if constexpr (AA == ADJ_ALGORITHM::INSERT)
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_insert(p1,p2);};
			}else
			{
				shuffel_method = [this](tsp64_t p1, tsp64_t p2){ this->adj_invert(p1,p2);};
			}
			
			ref_time =  std::chrono::high_resolution_clock::now();

			this->solve(cooling_method, shuffel_method);

		}
		tsp64_t get_result()
		{
			return this->best_cost;
		}

		void show_results()
		{
			fmt::print( "{} \n", this->best_cost );
			path_manager::show( this->best_path );
		}

	private:

		inline double calc_probability(double delta)
		{
			return std::exp(-delta / (this->temperature));
		}
		
		inline void calc_time()
		{
			current_time = std::chrono::high_resolution_clock::now();
			diff = current_time - ref_time;
			time = diff.count();
		}
		inline void calc_time2(){
			time++;
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


		inline void logarithm_cooling()
		{
			calc_time2();
			this->temperature = begin_temperature/std::log(time +1.01);
		}
		
		inline void geometric_cooling()
		{
			calc_time2();
			this->temperature = begin_temperature*std::pow(cooling_rate,time);	
		}

		inline void linear_cooling()
		{
			calc_time2();
			this->temperature = begin_temperature - (cooling_rate*time);
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

			
		void solve(std::function<void(void)> &cool_down, std::function<void(tsp64_t,tsp64_t)> &shuffle)
		{

		    this->current_cost = TSP::path_manager::calculate_cost(this->current_path, this->m_ref);
		    this->best_cost = this->current_cost;
		    this->best_path = this->current_path;
		     
		    while (this->temperature > this->final_temperature && time < begin_temperature )
		    {
		    	tsp64_t lower_cost = std::numeric_limits<tsp64_t>::max();
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

						if( lower_cost > cost )
						{
							lower_cost = cost;
							p1 = i;
							p2 = j;
						}
					}
				}

				cool_down();

		        double delta_distance = lower_cost - current_cost;
		        
		        if ( delta_distance < 0 || (delta_distance > 0 && 
		             calc_probability(delta_distance) > random(0.0, 1.0)))
		        {
		            current_cost = lower_cost;
		            shuffle(p1,p2);
		        }

		        if(this->current_cost < this->best_cost)
		        {
		        	this->best_cost = this->current_cost;
		        	this->best_path = this->current_path;
		        }
		    }
		}

	};

}