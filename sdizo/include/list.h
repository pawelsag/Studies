#ifndef SDIZO_LIST
#define SDIZO_LIST

#include "container_base.h"
#include <initializer_list>

struct node{
	node* next;
	node* prev;
	int32_t value; 
};

class list : public container_base 
{
	node *front = nullptr; // pointer to data structure
	node *tail = nullptr; // pointer to data structure
	
	int32_t count = 0;		// amount of elements in table 
	int32_t top_index = 0; // index to currently inserted tem 
public:
	list() =default;
	list(std::initializer_list<int32_t> args_vector);
	
	void generate_list(int32_t size);

	void push_back(int32_t value);

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

	bool load_from_file(std::string FileName) override;

	int32_t find(int32_t value) override;
	
	bool insert(int32_t index, int32_t value) override;

	bool remove(int32_t index) override;

	void display() override;

};

#endif