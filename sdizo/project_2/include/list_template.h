#ifndef SDIZO_LIST_TMP
#define SDIZO_LIST_TMP

#include <initializer_list>
#include "common_struct.h"


template<typename T>
class list
{
	friend class iterator;

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
	

	template<typename Payload_t = T>
	class iterator{
		list<Payload_t> *master;
		node<Payload_t> *current_item;
	public:

		iterator() = delete;
		iterator(list<Payload_t>* li){
			master = li;
			current_item = master->head;
		}
		~iterator() = default;

		Payload_t* get_and_next(){
			if(current_item == nullptr)
				return nullptr;
			Payload_t *val = &current_item->value;
			current_item = current_item->next;
			return val;
		}
	};

	iterator<T> get_iter(){
		return iterator<T>(this);
	}

};

#include "../src/list_template.cpp"


#endif