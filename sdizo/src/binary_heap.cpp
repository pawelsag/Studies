#include "binary_heap.h"
#include <time.h>
#include <random>
#include <fstream>
#include<iostream>

binary_heap::binary_heap(){
	this->size = binary_heap::REDUNDANT_SIZE;
	this->tab = new int32_t[this->size];
	// variables used in printing
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;

}

binary_heap::binary_heap(std::initializer_list<int32_t> args_vector){
	
	for (auto&& val : args_vector){
		this->push_back(val);
	}
	// variables used in printing
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

binary_heap::~binary_heap(){
	delete [] this->tab;
}

void binary_heap::generate_data(int32_t size){
	srand(time(0));
	for(int i =0; i < size; i++){
		this->push_back( rand() %1337 );
	}
}

void binary_heap::clear(){
	this->elements = 0;
	this->size = binary_heap::REDUNDANT_SIZE;
	delete [] this->tab;
	this->tab = new int32_t[this->size];	
}

bool binary_heap::load_from_file(std::string file_name){
	this->elements =0; 

	std::fstream fs (file_name, std::fstream::in | std::fstream::out);
	
	if (!fs.is_open())
		return false;

	int value, elements_count;
	// read size
	fs>>elements_count;
	// read data from file until eof
	while( (elements_count--) ){
		fs >> value;
		this->push_back(value);
	}
	fs.close();
	return true;
}

int32_t binary_heap::find(int32_t key){
	// loop whole table and search for item
	for(int i =0; i < this->elements; i++)
		if(this->tab[i] == key)
			return i;
	return -1;
}


bool binary_heap::push_back(int32_t key){
	if(this->elements >= this->size){
		if( !this->realloc(MEMORY_OP::RESIZE_UP))
			return false;
	}
	// put child in heap
	this->tab[this->elements] = key;
	// get parent index
	int32_t parent = this->parent(this->elements);
	// copy last index
	int32_t element_idx = this->elements;
	// do heapify
	while(element_idx > 0 && this->tab[parent] < key){
		std::swap(this->tab[parent], this->tab[element_idx]);
		element_idx = parent;
		parent =  this->parent(element_idx);
	}
	this->elements++;
	return true;
}


// remove element from heap by given value 
bool binary_heap::remove(int32_t key){
	if(this->elements < this->size - binary_heap::REDUNDANT_SIZE ){
		if( !this->realloc(MEMORY_OP::RESIZE_UP))
			return false;
	}

	int32_t key_idx = this->find(key);
	if(key_idx == -1) 
		return false;

	int32_t l_child_idx, r_child_idx;
	int32_t max_element, max_index;

	// swap found item with last element
	std::swap(this->tab[key_idx], this->tab[ this->elements - 1 ]);
	// get children
	l_child_idx = this->left_child(key_idx);
	r_child_idx = this->right_child(key_idx);
	// while index of currently handled child is bigger than last element index 
	while(l_child_idx < this->elements-1){
		// find smallest child
		if(this->tab[l_child_idx] > this->tab[r_child_idx] || r_child_idx >= this->elements){
			max_element  = this->tab[l_child_idx];
			max_index =l_child_idx;
		}else{
			max_element  = this->tab[r_child_idx];
			max_index =r_child_idx;			
		}
		// if child is smaller than currently handled element
		// stop heapifing
 		if(max_element < this->tab[key_idx])
			break;
		// otherwise spaw elements
		std::swap(this->tab[ key_idx ], this->tab[ max_index ]);
		// get new children
		l_child_idx = this->left_child(max_index);
		r_child_idx = this->right_child(max_index);
		key_idx =max_index;
	}
	
	this->elements--;

	return true;
}

void binary_heap::display(std::string sp, std::string sn, int v){
  std::string s;

  if(v < this->elements)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    this->display(s + cp, cr, this->right_child(v) );

    s = s.substr(0,sp.length()-2);

    std::cout << s << sn <<this->tab[v] << std::endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    this->display(s + cp, cl, this->left_child(v));
  }
}

