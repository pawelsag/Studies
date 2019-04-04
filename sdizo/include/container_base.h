#ifndef CONTAINER_BASE
#define CONTAINER_BASE

#include <string>
#include <stdint.h>
#include <fstream>

class container_base
{

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

	virtual void perform_test(std::fstream& write, int32_t population_size, int32_t* population = nullptr, int32_t* indexes =nullptr)=0;

};

#endif