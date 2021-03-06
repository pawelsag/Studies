#include "binary_heap.h"
#include <iostream>
#include <random>
#include <chrono>
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

void binary_heap::clear(){
	this->elements = 0;
	this->size = binary_heap::REDUNDANT_SIZE;
	delete [] this->tab;
	this->tab = new int32_t[this->size];	
}

bool binary_heap::find(int32_t value){
	if(this->find_index(value) == -1)
		return false;
	return true;
}	

int32_t binary_heap::find_index(int32_t key){
	// loop whole table and search for item
	for(int i =0; i < this->elements; i++)
		if(this->tab[i] == key)
			return i;
	return -1;
}



void binary_heap::push_back(int32_t key){
	if(this->elements >= this->size){
		if( !this->realloc(MEMORY_OP::RESIZE_UP)){
			this->is_ok =false;
			return;
		}
	}
	// put child in heap
	this->tab[this->elements] = key;
	// get parent index
	int32_t parent = this->parent(this->elements);
	// copy last index
	int32_t element_idx = this->elements;
	// do heapify
#ifdef HEAP_MIN
	while(element_idx > 0 && this->tab[parent] > key){
#else
	while(element_idx > 0 && this->tab[parent] < key){
#endif	
		std::swap(this->tab[parent], this->tab[element_idx]);
		element_idx = parent;
		parent =  this->parent(element_idx);
	}
	
	this->elements++;

	this->is_ok = true;
}


// remove element from heap by given value 
bool binary_heap::remove(int32_t key){
	if(this->elements < this->size - binary_heap::REDUNDANT_SIZE ){
		if( !this->realloc(MEMORY_OP::RESIZE_DOWN))
			return false;
	}

	int32_t key_idx = this->find_index(key);
	if(key_idx == -1) 
		return false;

	int32_t l_child_idx, r_child_idx, parent;
	int32_t max_element, max_index;

	this->elements--;
	// swap found item with last element
	std::swap(this->tab[key_idx], this->tab[ this->elements ]);
	key = this->tab[key_idx];

	// get children
	l_child_idx = this->left_child(key_idx);
	r_child_idx = this->right_child(key_idx);

	// while index of currently handled child is bigger than last element index 
	while(l_child_idx < this->elements-1){
		
		// find smallest child
	#ifdef HEAP_MIN
		if(this->tab[l_child_idx] < this->tab[r_child_idx] || r_child_idx >= this->elements){
	#else
		if(this->tab[l_child_idx] > this->tab[r_child_idx] || r_child_idx >= this->elements){
	#endif
			max_element  = this->tab[l_child_idx];
			max_index =l_child_idx;
		}else{
			max_element  = this->tab[r_child_idx];
			max_index =r_child_idx;			
		}
		// if child is smaller than currently handled element
		// stop heapifing
	#ifdef HEAP_MIN
		if(max_element > this->tab[key_idx])
			break;
	#else
		if(max_element < this->tab[key_idx])
			break;
	#endif
 		
		// otherwise swap elements
		std::swap(this->tab[ key_idx ], this->tab[ max_index ]);
		// get new children
		l_child_idx = this->left_child(max_index);
		r_child_idx = this->right_child(max_index);
		key_idx =max_index;
	}
	
	parent =  this->parent(key_idx);
 
	// do heapify when elemets should move to upper layers
#ifdef HEAP_MIN
	while(key_idx > 0 && this->tab[parent] > key){
#else
	while(key_idx > 0 && this->tab[parent] < key){
#endif
		std::swap(this->tab[parent], this->tab[key_idx]);
		key_idx = parent;
		parent =  this->parent(key_idx);
	}
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

void binary_heap::display(){
	this->display("","", 0);
}

void binary_heap::perform_test(int32_t value, [[maybe_unused]]int32_t index ){
	using namespace std;
	using namespace std::chrono;
	// chrono measure variables
	std::chrono::nanoseconds time_span;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
			

	
  // random insert test   
  std::cout << "HEAP::Wstawianie wartosci"<<endl;
    
  t1 = high_resolution_clock::now(); 
  this->push_back(value); 
  t2 = high_resolution_clock::now();

  time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
  std::cout << std::endl;
  // udpate results
  this->update_average(time_span.count(), OPERATION_TYPE::INSERT);


  // search test;
  std::cout << "HEAP::Wyszukiwanie sposrod " << this->elements <<" egzemplarzy"<<endl;
  t1 = high_resolution_clock::now();
  this->find(value); 
  t2 = high_resolution_clock::now();

  time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
  std::cout << std::endl;
  
  // udpate results
  this->update_average(time_span.count(), OPERATION_TYPE::SEARCH);  

  
  // random delete test;
  std::cout << "HEAP::Usuwanie wartosci"<<endl;
  t1 = high_resolution_clock::now();
  this->remove(value); 
  t2 = high_resolution_clock::now();

  time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
  std::cout << std::endl;
  // udpate results
  this->update_average(time_span.count(), OPERATION_TYPE::REMOVE);

}
