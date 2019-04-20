#include "table.h"
#include <iostream>
#include <algorithm>
#include <new>
#include <random>
#include <chrono>


table::table(std::initializer_list<int32_t> args_vector){
	for (auto&& val : args_vector){
		this->push_back(val);
	}
}

table::~table(){
	if(this->tab != nullptr)
		delete [] this->tab;
}

void table::push_back(int32_t value){
	this->insert(this->count,value);
}

void table::push_front(int32_t value){
	this->insert(0,value);
}
void table::pop_back(){
	this->remove(this->count-1);
}

void table::pop_front(){
	this->remove(0);
}

bool table::insert(int32_t index, int32_t value){
	
	if(index < 0 || index > this->count)
		return false;

	int32_t *temp;
	// try to allocate memory
	try{
		temp = new int32_t[ this->count + 1 ];
	}catch(const std::bad_alloc& e){
		std::cout << "BAD ALLOC"<<std::endl;
		return false;
	}

	if(this->tab == nullptr){
		this->tab = new int32_t[ this->count + 1 ];
		this->tab[0] = value;
		this->count++;
		return true;
	}
	// copy old table without index
	std::copy(this->tab, this->tab + index, temp);
	// left one empty cell for item
	std::copy(this->tab + index, this->tab + this->count, temp + index + 1);
	// append new element
	temp[index] = value;
	// remove old table
	delete [] this->tab;
	// set new table to main table pointer
	this->tab = temp;

	this->count++;

	return true;
}

bool table::remove(int32_t index){
	
	if(index < 0 || index >= this->count)
		return false;
	
	// if there is only one elemnt 
	// free space and return
	if(this->count == 1){
		delete[] this->tab;
		this->tab = nullptr;
		this->count--;
		return true;
	// if there is no elements	
	}else if(this->count == 0 )
		return false;

	int32_t *temp;
	// try to allocate memory
	try{
		temp = new int32_t[ this->count - 1];
	}catch(const std::bad_alloc& e){
		return false;
	}

	// copy old table without index
	std::copy(this->tab, this->tab + index, temp);
	std::copy(this->tab + index + 1 , this->tab + this->count, temp + index);
	// remove old table
	delete [] this->tab;
	// set new table to main table pointer
	this->tab = temp;
	this->count--;

	return true;
}
bool table::find(int32_t value){
	if(this->find_index(value) == -1)
		return false;
	return true;
}	


int32_t table::find_index(int32_t value){
	// loop whole table and search for item
	for(int i =0; i < this->count; i++)
		if(this->tab[i] == value)
			return i;
	return -1;
}

void table::clear(){
	int copy_count =  this->count;
	for (int i = 0; i < copy_count; ++i)
	{
		this->pop_front();
	}
}

void table::display(){
	if(this->count == 0){
		std::cout << "[]"<<std::endl;
		return;
	}
	std::cout<< "[ ";
	for (int i = 0; i < this->count-1; ++i)
	{
		 std::cout<< this->tab[i] <<", ";
	}
	std::cout<< this->tab[this->count-1] << " ]"<<std::endl;;
}


void table::perform_test(int32_t value, int32_t index){
	using namespace std;
	using namespace std::chrono;
	// chrono measure variables
	std::chrono::nanoseconds time_span;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
	
	// random insert test		
  std::cout << "TABLICA::Wstawianie wartosci"<<endl;
  	
	t1 = high_resolution_clock::now(); 
	this->insert(index, value); 
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::INSERT);


	// search test;
  	std::cout << "TABLICA::Wyszukiwanie sposrod " << this->count <<" egzemplarzy"<<endl;
	t1 = high_resolution_clock::now();
	this->find(value); 
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::SEARCH);	

	
	// random delete test;
	std::cout << "TABLICA::Usuwanie wartosci"<<endl;
	t1 = high_resolution_clock::now();
  this->remove(index); 
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::REMOVE);

	// push back test;
	std::cout << "TABLICA::Dodanie na koniec " << endl;
	t1 = high_resolution_clock::now();
	this->push_back(value); 
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::PUSH_BACK);	
	
	// back delete test;
  	std::cout << "TABLICA::Usuwanie z konca " << endl;
	t1 = high_resolution_clock::now();
  this->pop_back(); 
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::POP_BACK);
	
	// push front test;
  	std::cout << "TABLICA::Wstwianie na poczatek "<<endl;
	t1 = high_resolution_clock::now();
	this->push_front(value);	
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::PUSH_FRONT);
	

	// front delete test;
	std::cout << "TABLICA::Usuwanie z poczatku "<<endl;
	t1 = high_resolution_clock::now();
	this->pop_front(); 	
	t2 = high_resolution_clock::now();

	time_span = chrono::duration_cast<chrono::nanoseconds>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " nanosekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::POP_FRONT);
}