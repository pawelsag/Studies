#ifndef SDIZO_LIST_TMP
#define SDIZO_LIST_TMP

#include <initializer_list>
#include "common_struct.h"


template<typename T>
class list
{

	node<T> *head = nullptr; // pointer to data structure
	node<T> *tail = nullptr; // pointer to data structure
	
	int32_t count = 0;		// amount of elements in table 
public:
	list() = default;
	list(std::initializer_list<T> args_vector);
	~list();

	bool find(T value);
	
	bool insert(int32_t index, T value);
	// search value than remove it from list
	bool remove(T value);

	void display();

	void clear();
  
	void push_back(T value);

	void push_front(T value);

	void pop_back();
	
	void pop_front();

	node<T>* find_node(T value);

};


#include "../src/list_template.cpp"





#endif