#include "list.h"
#include <iostream>
#include <random>
#include <chrono>

list::list(std::initializer_list<int32_t> args_vector){
	for (auto&& val : args_vector){
		this->push_back(val);
	}
}

list::~list(){
	this->clear();
}

bool list::find(int32_t value){
	if(this->find_node(value) == nullptr)
		return false;
	return true;
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
	for(searched_item = this->head; i < index; searched_item = searched_item->next )++i;

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
	node* item_to_remove = this->find_node(value);
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

node* list::find_node(int32_t value){
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
	if(this->count == 0)
		return;
  if(this->count == 1)
    this->head = nullptr;
  
  node *node_to_remove = this->tail;
  if(node_to_remove->prev)
    node_to_remove->prev->next = nullptr;
  this->tail = node_to_remove->prev;
  delete node_to_remove;
  this->count--;
}

void list::pop_front(){
  if(this->count == 0)
    return;
  if(this->count == 1)
    this->tail = nullptr;
  
  node *node_to_remove = this->head;
  if(node_to_remove->next)
    node_to_remove->next->prev = nullptr;
  this->head = node_to_remove->next;
  delete node_to_remove;
  this->count--;
}

void list::clear(){
	int copy_count =  this->count;
	for (int i = 0; i < copy_count; ++i)
	{
		this->pop_front();
	}
}

void list::perform_test( int32_t population_size, int32_t* population , int32_t* indexes){

	using namespace std;
	using namespace std::chrono;
	// chrono measure variables
	duration<double> time_span;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
			

		// random insert test		
  	std::cout << "Wstawianie losowe " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size; ++j)
	{
		this->insert(indexes[j], population[j]); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::INSERT);


	// search test;
  	std::cout << "Wyszukiwanie "<< population_size << " wartosci sposrod " << population_size <<" egzemplarzy"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size ; ++j)
	{
		this->find(population[indexes[j]]); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::SEARCH);	

	
	// random delete test;
  	std::cout << "Usuwanie losowe " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = population_size-1; j >=0 ; --j)
	{
		this->remove(indexes[j]); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::REMOVE);		
  this->clear();

	// push back test;
  	std::cout << "Dodanie na koniec " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size ; ++j)
	{
		this->push_back(population[j]); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::PUSH_BACK);	
	
	// back delete test;
  	std::cout << "Usuwanie z konca " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size ; ++j)
	{
		this->pop_back(); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::POP_BACK);
	
	// push front test;
  	std::cout << "Wstwianie na poczatek " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size; ++j)
	{
		this->push_front(population[j]);
	}
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::PUSH_FRONT);
	

	// front delete test;
	std::cout << "Usuwanie z poczatku " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size; ++j)
	{
		this->pop_front(); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::POP_FRONT);

}
