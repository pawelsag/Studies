#ifndef SDIZO_LIST
#define SDIZO_LIST

#include "container_base.h"
#include <initializer_list>

struct node{
	node* next = nullptr;
	node* prev = nullptr;
	int32_t value = 0; 
};

class list_sdizo : public container_base 
{
	node *head = nullptr; // pointer to data structure
	node *tail = nullptr; // pointer to data structure
	
	int32_t count = 0;		// amount of elements in table 
public:
	list_sdizo() = default;
	list_sdizo(std::initializer_list<int32_t> args_vector);
	~list_sdizo();

	bool find(int32_t value) override;
	
	bool insert(int32_t index, int32_t value) override;
	// search value than remove it from list
	bool remove(int32_t value) override;

	void display() override;

	void clear()override;

  void perform_test(int32_t value, int32_t index ) override;
  
private:
	void push_back(int32_t value)override;

	void push_front(int32_t value);

	void pop_back();
	
	void pop_front();

	node* find_node(int32_t value);

};

#endif