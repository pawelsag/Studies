#ifndef SDIZO_TABLE
#define SDIZO_TABLE

#include "container_base.h"
#include <initializer_list>

class table : public container_base 
{
	int32_t *tab = nullptr; // pointer to data structure 
	int32_t count = 0;     // point to the element one after last element
						   // this is also the container element counter   	
public:
	table()=default;
	table(std::initializer_list<int32_t> args_vector);
	~table();

	void clear();

	bool find(int32_t value) override;

	// indexes starts from 0 up to count-1	
	bool insert(int32_t index, int32_t value) override;
	
	// indexes starts from 0 up to count-1
	bool remove(int32_t index) override;

	void display() override;

	void perform_test(std::fstream& write, int32_t population_size, int32_t* population = nullptr, int32_t* indexes =nullptr) override;

private:
	void push_back(int32_t value);

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

	int32_t find_index(int32_t value);
};

#endif