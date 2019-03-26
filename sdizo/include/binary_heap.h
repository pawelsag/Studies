#ifndef SDIZO_HEAP
#define SDIZO_HEAP

#include "container_base.h"
#include <initializer_list>
#include <algorithm>
#include <new>
#include <string>
class binary_heap 
{
	static constexpr int32_t REDUNDANT_SIZE = 32; 

	int32_t *tab = nullptr; // pointer to data structure 
	
	int32_t size = 0;      // current heap size

	int32_t elements = 0; // amount of elements inserted to heap
						  // points to free space just after last element

	enum class MEMORY_OP{
		RESIZE_DOWN =0,
		RESIZE_UP =1,
	};
	std::string cr,cl,cp;

public:
	binary_heap();
	binary_heap(std::initializer_list<int32_t> args_vector);
	~binary_heap();

	void generate_data(int32_t size);

	void clear();

	bool load_from_file(std::string file_name);

	int32_t find(int32_t key);

	// push key to heap
	bool push_back(int32_t key);
	
	// remove element from heap by given value 
	bool remove(int32_t key);

	void display(std::string sp, std::string sn, int v);

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