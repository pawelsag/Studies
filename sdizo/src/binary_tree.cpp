#include "binary_tree.h"
#include <iostream>
#include <string>
#include <new>
#include <chrono>
binary_tree::binary_tree(){

	// variables used in printing
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
	
}

binary_tree::binary_tree(std::initializer_list<int32_t> args_vector){
	for (auto&& val : args_vector){
		this->push_back(val);
	}
	// variables used in printing
	cr = cl = cp = "  ";
	cr[0] = 218; cr[1] = 196;
	cl[0] = 192; cl[1] = 196;
	cp[0] = 179;
}

binary_tree::~binary_tree(){
	this->clear();
}

bool binary_tree::find(int32_t value){
	if(this->find_node(value) == nullptr)
		return false;
	return true;
}	

void binary_tree::clear(){
	BST_Node *rotate_element = this->root;
	// expand binary structure to straight line 
	while(rotate_element){
		if(rotate_element->left){
			this->rotate_left(rotate_element);
			rotate_element = rotate_element->up;
		}else{
			rotate_element = rotate_element->right;
		}
	}
	rotate_element = this->root;
	// delete all nodes from structure
	while(rotate_element){
		this->root = rotate_element->right;	
		delete rotate_element;
		rotate_element = this->root;
	}
	this->elements =0;
}

BST_Node* binary_tree::find_node(int32_t key){
	BST_Node *node = this->root ;
	while( node != nullptr && node->key != key ){
		if( node->key < key)
			node = node->right;
		else
		 	node = node->left;
	}
	return node;
}

void binary_tree::push_back(int32_t key){
	BST_Node *new_node;
	try{
		new_node = new BST_Node;
	}catch(const std::bad_alloc& e){
		is_ok = false;
		return;
	}
	new_node->left = nullptr;
	new_node->right = nullptr;
	new_node->key = key;

	BST_Node* top = this->root, *parent = nullptr;

	while(top != nullptr){
		parent = top;
		if (new_node->key < top->key)
			top = top->left;
		else
			top = top->right;
	}

	new_node->up = parent;
	if(parent == nullptr){
		this->root = new_node;
	}else if(new_node->key < parent->key)
		parent->left = new_node;
	else
		parent->right = new_node;
	this->elements++;
	this->is_ok = true;
	this->tree_DSW();
}

bool binary_tree::remove(int32_t key){
	BST_Node *node = this->find_node(key);
	if(node == nullptr)
		return false;

	BST_Node *node_to_remove, *child;
	
	// if node has at most one child
	if(node->left == nullptr || node->right == nullptr)
		node_to_remove = node;
	else // node has more than one child
		// find successor of current  child 
		node_to_remove = this->tree_succesor(node);

	// find child of removing node
	// the only possible scenario here is that 
	// node can have at most one child
	if(node_to_remove->left != nullptr)
		child = node_to_remove->left;
	else
		child = node_to_remove->right;

	if (child != nullptr) child->up = node_to_remove->up; 
	// if if removing node is the tree root
	if(node_to_remove->up == nullptr)
		// substitute root with its child 
		this->root = child; 
	else{
		//otherwise we need to substitute deleted node with its child 
		if(node_to_remove->up->left == node_to_remove)
			node_to_remove->up->left = child;
		else
			node_to_remove->up->right = child;
	}
	// if node we want to remove is successor
	if(node != node_to_remove){
		// copy data from successor
		node->key = node_to_remove->key;
	}
	delete node_to_remove;
	this->elements--;
	this->tree_DSW();
	
	return true;
}

void binary_tree::display(std::string sp, std::string sn,BST_Node* node){
  using namespace std;
  string s;
  if(node)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    this->display(s + cp, cr, node->right);

    s = s.substr(0,sp.length()-2);
    cout << s << sn << node->key << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    this->display(s + cp, cl, node->left);
  }
}

void binary_tree::rotate_right(BST_Node* A){
	if(A == nullptr) return;
	BST_Node *parent, *B;
	parent = A->up;
	// store A left element
	B = A->left;
	// it means that node do not have elements on his left 
	if(B){
		// store B right element
		A->left = B->right;
		// if current left element of A is not null
		// assign new parent
		if(A->left) A->left->up = A;
		// assign new right element
		B->right = A;
		B->up = parent;
		A->up = B;
		if(parent){
			if(parent->left == A)
				parent->left = B;
			else
				parent->right = B;
		}else
			// there was no parent
			// B is now the greatest node
			this->root = B;
	}
}

void binary_tree::rotate_left(BST_Node* A){
	if(A == nullptr) return;
	BST_Node *parent, *B;
	parent = A->up;
	// store A right element
	B = A->right;
	// it means that node do not have elements on his left 
	if(B){
		// store B left element
		A->right = B->left;
		// if current right element of A is not null
		// assign new parent
		if(A->right) A->right->up = A;
		// assign new left element
		B->left = A;
		B->up = parent;
		A->up = B;
		if(parent){
			if(parent->left == A)
				parent->left = B;
			else
				parent->right = B;
		}else
			// there was no parent
			// B is now the greatest node
			this->root = B;
	}
}

BST_Node* binary_tree::tree_succesor(BST_Node*node){
	if(node->right != nullptr)
		return this->tree_minimum(node->right);
	BST_Node* succesor = node->up;
	while(succesor != nullptr && succesor->right == node){
		node = succesor;
		succesor = succesor->up;
	}
	return succesor;
}
BST_Node* binary_tree::tree_predecessor(BST_Node*node){
	if(node->left != nullptr)
		return this->tree_maximum(node->left);

	BST_Node *succesor = node->up;
	while(succesor != nullptr && succesor->left == node){
		node = succesor;
		succesor = succesor->up;
	}
	return succesor;	
}

BST_Node* binary_tree::tree_maximum(BST_Node*node){
	BST_Node *max_node = node;
	while(max_node->right != nullptr)
		max_node = max_node->right;
	return max_node;
}

BST_Node* binary_tree::tree_minimum(BST_Node*node){
	BST_Node *min_node = node;
	while(min_node->left != nullptr)
		min_node = min_node->left;
	return min_node;
}

void binary_tree::tree_DSW(){
	BST_Node *rotate_element = this->root;
	int32_t n = this->elements, s;
	// expand binary structure to straight line 
	while(rotate_element){
		if(rotate_element->left){
			this->rotate_right(rotate_element);
			rotate_element = rotate_element->up;
		}else{
			rotate_element = rotate_element->right;
		}
	}

	s = n + 1 - this->calculate_DSW_num(n+1);
	rotate_element = this->root;
	for (int i = 0; i < s; ++i)
	{
		this->rotate_left(rotate_element);
		rotate_element = rotate_element->up->right;
	}

	n = n-s;
	while(n > 1){
		n>>= 1;
		rotate_element = this->root;
		for (int i = 0; i < n; ++i)
		{
			this->rotate_left(rotate_element);
			rotate_element = rotate_element->up->right;
		}
	}	
}

int32_t binary_tree::calculate_DSW_num(int32_t n){
  int32_t y = 1;

  while((n >>= 1) > 0) y <<= 1;

  return y;
}

void binary_tree::display(){
	this->display("","", this->root);
}

void binary_tree::perform_test( int32_t population_size, int32_t* population, int32_t* indexes ){
	using namespace std;
	using namespace std::chrono;
	// chrono measure variables
	duration<double> time_span;
	high_resolution_clock::time_point t1;
	high_resolution_clock::time_point t2;
			

	// random insert test		
  	std::cout << "Wstawianie " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size; ++j)
	{
		this->push_back( population[j] ); 
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
  std::cout << "Usuwanie " << population_size <<" wartosci"<<endl;
	t1 = high_resolution_clock::now();
	for (int32_t j = 0; j < population_size; ++j)
	{
	  this->remove(population[j]); 
	}		
	t2 = high_resolution_clock::now();

	time_span = duration_cast<duration<double>>(t2 - t1);

	std::cout << "Zajelo :" << time_span.count() << " sekund.";
	std::cout << std::endl;
	// udpate results
	this->update_average(time_span.count(), OPERATION_TYPE::REMOVE);	
  this->clear();
}