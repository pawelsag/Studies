#ifndef CONTAINER_BASE
#define CONTAINER_BASE

#include <string>
#include <stdint.h>
#include <fstream>
enum class OPERATION_TYPE{
	INSERT      = 0,
	SEARCH      = 1,
	REMOVE      = 2,
	PUSH_BACK   = 3,
	POP_BACK    = 4,
	PUSH_FRONT  = 5,
	POP_FRONT   = 6
};

constexpr const size_t TEST_COUNT = 7;
constexpr const size_t POPULATION_SIZE = 30;
class container_base
{
	double performance_average[TEST_COUNT] = {};
	size_t n[TEST_COUNT] = {};

public:
	container_base() {};
	~container_base() {};

	void generate_data(int32_t);

	void load_from_file(std::string); 

	virtual bool insert(int32_t, int32_t)=0;

	virtual bool remove(int32_t)=0;

	virtual bool find(int32_t)=0;

	virtual void display()=0;

	virtual void clear()=0;

	virtual void push_back(int32_t value)=0;

	virtual void perform_test(int32_t population_size, int32_t* population = nullptr, int32_t* indexes =nullptr)=0;

	void save_test_averege(std::fstream& write){
		for(auto i = 0llu; i < TEST_COUNT; i++){
			if(n[i] != 0) 
				write << this->performance_average[i] / this->n[i] << ";";
		}
	}

	void reset_average(){
		for(auto i = 0llu; i < TEST_COUNT; i++ ){
			this->n[i] = 0;
			this->performance_average[i] = 0;
		}
	}

	void update_average(double value, OPERATION_TYPE type){
		this->n[static_cast<size_t>(type)]++;
		this->performance_average[static_cast<size_t>(type)] += value;
	}
};

#endif