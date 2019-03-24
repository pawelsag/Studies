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
	void generate_table(int32_t size);

	void push_back(int32_t value);

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

	void clear();

	bool load_from_file(std::string file_name) override;

	int32_t find(int32_t value) override;
	
	bool insert(int32_t index, int32_t value) override;

	bool remove(int32_t index) override;

	void display() override;

};

#endif