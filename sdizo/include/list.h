#ifndef SDIZO_LIST
#define SDIZO_LIST

#include "container_base.h"
#include <initializer_list>

struct node{
	node* next = nullptr;
	node* prev = nullptr;
	int32_t value = 0; 
};

class list : public container_base 
{
	node *head = nullptr; // pointer to data structure
	node *tail = nullptr; // pointer to data structure
	
	int32_t count = 0;		// amount of elements in table 
public:
	list() = default;
	list(std::initializer_list<int32_t> args_vector);
	~list();

	bool find(int32_t value) override;
	
	bool insert(int32_t index, int32_t value) override;
	// search value than remove it from list
	bool remove(int32_t value) override;

	void display() override;

	void clear();

	void perform_test(std::fstream& write, int32_t population_size, int32_t* population =nullptr, int32_t* indexes =nullptr);

private:
	void push_back(int32_t value);

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

	node* find_node(int32_t value);

};

#endif