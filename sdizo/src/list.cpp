#include "list.h"
#include <iostream>
#include <time.h>
#include <random>
#include <fstream>

list::list(std::initializer_list<int32_t> args_vector){
	for (auto&& val : args_vector){
		this->push_back(val);
	}
}

void list::generate_data(int32_t size){
	srand(time(0));
	for(int i =0; i < size; i++){
		this->push_back( rand() %1337 );
	}
}

bool list::load_from_file(std::string file_name){
	this->clear(); 

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

list::~list(){
	this->clear();
}
bool list::insert(int32_t index, int32_t value){
	if(index < 0 || index > this->count )
		return false;
	// if we want prepend item
	if(index == 0){
		this->push_front(value);
		return true;
	}
	// if we wantt append item 
	if(index == this->count){
		this->push_back(value);
		return true;
	}
	// create new node
	node* tmp = new node;  
    // add value to created node 
    tmp->value = value;  

	// we want to insert item before an element
	// which is indicated by index
	node* searched_item;
	int32_t i = 0;
	for(searched_item = this->head; i < index; searched_item = searched_item->next );

	// when we get desired item
	// set next and prev element for new item
	tmp->next = searched_item;
	tmp->prev = searched_item->prev;
	// set prev pointer of item which is after 
	// our new_item to indicate our new_item   
	searched_item->prev = tmp;
	// set next pointer of item which is before 
	// our new_item to indicate our new_item
	tmp->prev->next =tmp;

	this->count++;
	return true;
}

bool list::remove(int32_t value){

	// find desired element
	node* item_to_remove = this->find(value);
	if( item_to_remove == nullptr)
		return false;
	
	if(item_to_remove->prev) 
		item_to_remove->prev->next = item_to_remove->next;
	else 
		this->head = item_to_remove->next;
	if(item_to_remove->next) 
		item_to_remove->next->prev = item_to_remove->prev;
	else        
		this->tail = item_to_remove->prev;
	
	delete item_to_remove;

	this->count--;
	return true;
}

node* list::find(int32_t value){
	node* item;
	for(item = this->head; item; item = item->next)
		if(item->value == value)
			break;
	return item;
}

void list::display(){
	using std::cout;
	using std::endl;

	cout<< "Lista HEAD ---> TAIL"<<endl;
	
	for (node* item = this->head; item; item = item->next){
		if(item->next != nullptr)
			cout << item->value <<" --> ";
		else
			cout << item->value;
	}
	cout<<endl;

	cout<< "Lista TAIL ---> HEAD"<<endl;
	
	for (node* item = this->tail; item; item = item->prev){
		if(item->prev != nullptr)
			cout << item->value <<" --> ";
		else
			cout << item->value;
	}
	cout<<endl;
}

void list::push_back(int32_t value){
	// create new node
	node* tmp = new node;  
    // add value to created node 
    tmp->value = value;  
  	// set pointer 
    tmp->next = nullptr;  
    tmp->prev = this->tail;  
  	this->tail = tmp;

  	// if last elements points somewhere
  	if( tmp->prev )
  		tmp->prev->next = tmp;
  	else
  		this->head = tmp;

    this->count++;  	
}

void list::push_front(int32_t value){
	// create new node
	node* tmp = new node;  
    // add value to created node 
    tmp->value = value;  
  	// set pointer 
    tmp->next = this->head;  
    tmp->prev = nullptr;  
  	this->head = tmp;

  	// if last elements points somewhere
  	if( tmp->next )
  		tmp->next->prev = tmp;
  	else
  		this->tail = tmp;

	this->count++;	
}

void list::pop_back(){
	if(this->count > 0)
		this->remove(this->tail->value);
}

void list::pop_front(){
	if(this->count > 0)
		this->remove(this->head->value);
}

void list::clear(){
	int copy_count =  this->count;
	for (int i = 0; i < copy_count; ++i)
	{
		this->pop_front();
	}
}