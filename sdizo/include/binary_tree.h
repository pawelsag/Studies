#ifndef SDIZO_HEAP
#define SDIZO_HEAP

#include "container_base.h"
#include <initializer_list>
#include <algorithm>
#include <new>
#include <string>
struct BST_Node
{
	BST_Node* up;
	BST_Node* left;
	BST_Node* right;
	int32_t key; // this variable is in the same time the key and our data 
};

class binary_tree 
{
	static constexpr int32_t REDUNDANT_SIZE = 32; 

	BST_Node* root = nullptr; // pointer to data structure 
	
	int32_t elements = 0; // amount of elements inserted to heap
						  // points to free space just after last element
	std::string cr,cl,cp;

public:
	binary_tree()=default;
	binary_tree(std::initializer_list<int32_t> args_vector);
	~binary_tree();

	void generate_data(int32_t size);

	void clear();

	bool load_from_file(std::string file_name);

	BST_Node* find(int32_t key);

	// push key to heap
	bool push_back(int32_t key);
	
	// remove element from heap by given value 
	bool remove(int32_t key);

	void display(std::string sp, std::string sn, int v);

};

#endif