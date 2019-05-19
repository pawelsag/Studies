#ifndef SDIZO_HEAP
#define SDIZO_HEAP

#include <initializer_list>
#include <algorithm>
#include <new>
#include <stdint.h>
#include <string>
// default implementation of the heap is maximum
#define HEAP_MIN

template <typename T>
class binary_heap
{

protected:
	static constexpr int32_t REDUNDANT_SIZE = 100; 

	T *tab = nullptr; // pointer to data structure 
	
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
	binary_heap(std::initializer_list<T> args_vector);
	~binary_heap();

	void clear();

	bool find(T key);

	// push key to heap
	void push_back(T key);

	virtual void display();

	void display(std::string sp, std::string sn, int v);
	
	// the key is the only value we need to delete node
	// based on the key we will know where desired item lies
	virtual bool remove(T key);
	
	int32_t update_node(int32_t key_idx, T data){

		this->tab[key_idx] = data;
		key_idx = this->heap_up(key_idx);
		key_idx = this->heap_down(key_idx);
		return key_idx;
	}
	
	// get index by given key
	int32_t find_index(T key);

protected:
	inline int32_t left_child(int32_t idx){
		return idx*2 + 1;
	}
	inline int32_t right_child(int32_t idx){
		return idx*2 + 2;
	}
	inline int32_t parent(int32_t idx){
		return (idx-1)/2; // int cast should floor it
	}	

	virtual int32_t heap_up(int32_t key_idx);
	virtual int32_t heap_down(int32_t key_idx);
	
	// automaticly expand or shrink size
	// depends on size
	bool realloc(MEMORY_OP operation){
		T* temp;
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
				temp = new T[new_size];
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
				temp = new T[new_size];
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

#include "../src/heap_template.cpp"

#endif