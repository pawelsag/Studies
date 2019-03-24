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
	list() =default;
	list(std::initializer_list<int32_t> args_vector);
	
	void generate_data(int32_t size) override;

	bool load_from_file(std::string FileName) override;

	node* find(int32_t value);
	
	bool insert(int32_t index, int32_t value) override;
	// search value than remove it from list
	bool remove(int32_t value) override;

	void display() override;

	void clear();
private:
	void push_back(int32_t value);

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

};

#endif