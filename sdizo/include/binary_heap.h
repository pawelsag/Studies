#ifndef SDIZO_HEAP
#define SDIZO_HEAP

#include "container_base.h"
#include <initializer_list>
#include <algorithm>
#include <new>

class binary_heap : public container_base 
{
	static constexpr int32_t REDUNDANT_SIZE = 32; 

	int32_t *tab = nullptr; // pointer to data structure 
	
	int32_t size = 0;      // current heap size

	int32_t elements = 0; // amount of elements inserted to heap
						  // points to free space just after last element

	bool is_ok = true;
	enum class MEMORY_OP{
		RESIZE_DOWN =0,
		RESIZE_UP =1,
	};
	std::string cr,cl,cp;

public:
	binary_heap();
	binary_heap(std::initializer_list<int32_t> args_vector);
	~binary_heap();

	void clear();

	bool find(int32_t key) override;

	// push key to heap
	void push_back(int32_t key);

	void display() override;

	void display(std::string sp, std::string sn, int v);

	// the key is the only value we need to create new node
	// based on key we will know where to put new item 
	bool insert(int32_t key, [[maybe_unused]]int32_t index = -1) {
		this->push_back(key);
		return this->is_ok;
	};
	
	// the key is the only value we need to delete node
	// based on the key we will know where desired item lies
	bool remove(int32_t key);

  void perform_test(int32_t value,[[maybe_unused]]int32_t index ) override;

private:
	inline int32_t left_child(int32_t idx){
		return idx*2 + 1;
	}
	inline int32_t right_child(int32_t idx){
		return idx*2 + 2;
	}
	inline int32_t parent(int32_t idx){
		return (idx-1)/2; // int cast should floor it
	}

	// get index by given key
	int32_t find_index(int32_t key);

	// automaticly expand or shrink size
	// depends on size
	bool realloc(MEMORY_OP operation){
		int32_t* temp;
		int32_t new_size;
		if(operation == MEMORY_OP::RESIZE_DOWN){
			// heap size shouldn't be zero
			// don't deallocate memory if we reach
			// the smaller posible size 
			if(this->size <= binary_heap::REDUNDANT_SIZE)
				return false;
			// create new table  
			new_size = this->size - binary_heap::REDUNDANT_SIZE;
			try{
				temp = new int32_t[new_size];
			}catch(std::bad_alloc& e){
				return false;
			}
			// copy old values
			std::copy(this->tab, this->tab + new_size, temp);
			// remove old table
			delete [] this->tab;
			// assign new size and table
			this->tab = temp;
			this->size = new_size;
		}
		else{
			// description for this part is same as for previous 
			new_size = this->size + binary_heap::REDUNDANT_SIZE;
			try{
				temp = new int32_t[new_size];
			}catch(std::bad_alloc& e){
				return false;
			}
			std::copy(this->tab, this->tab + this->size, temp);
			delete [] this->tab;
			this->tab = temp;
			this->size = new_size;
		}
		return true;		 
	}
};

#endif