#include <iostream>

template<typename T>
list<T>::list(std::initializer_list<T> args_vector){
	for (auto&& val : args_vector){
		this->push_back(val);
	}
}

template<typename T>
list<T>::~list(){
	this->clear();
}

template<typename T>
bool list<T>::find(T value){
	if(this->find_node(value) == nullptr)
		return false;
	return true;
}

template<typename T>
bool list<T>::insert(int32_t index, T value){
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
	node<T>* tmp = new node<T>;  
    // add value to created node 
    tmp->value = value;  

	// we want to insert item before an element
	// which is indicated by index
	node<T>* searched_item;
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

template<typename T>
bool list<T>::remove(T value){

	// find desired element
	node<T>* item_to_remove = this->find_node(value);
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

template<typename T>
node<T>* list<T>::find_node(T value){
	node<T>* item;
	for(item = this->head; item; item = item->next)
		if(item->value == value)
			break;
	return item;
}

template<typename T>
void list<T>::display(){
	using std::cout;
	using std::endl;

	for (node<T>* item = this->head; item; item = item->next){
		if(item->next != nullptr)
			cout << item->value <<", ";
		else
			cout << item->value;
	}
	cout<<endl;
}

template<typename T>
void list<T>::push_back(T value){
	// create new node
	node<T>* tmp = new node<T>;  
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

template<typename T>
void list<T>::push_front(T value){
  	// create new node
	  node<T>* tmp = new node<T>;  
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

template<typename T>
void list<T>::pop_back(){
	if(this->count == 0)
		return;
  if(this->count == 1)
    this->head = nullptr;
  
  node<T> *node_to_remove = this->tail;
  if(node_to_remove->prev)
    node_to_remove->prev->next = nullptr;
  this->tail = node_to_remove->prev;
  
  delete node_to_remove;
  this->count--;
}

template<typename T>
void list<T>::pop_front(){
  if(this->count == 0)
    return;
  if(this->count == 1)
    this->tail = nullptr;
  
  node<T> *node_to_remove = this->head;
  if(node_to_remove->next)
    node_to_remove->next->prev = nullptr;
  this->head = node_to_remove->next;
  delete node_to_remove;
  this->count--;
}

template<typename T>
void list<T>::clear(){
	int copy_count =  this->count;
	for (int i = 0; i < copy_count; ++i)
	{
		this->pop_front();
	}
}