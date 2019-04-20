#ifndef SDIZO_TREE
#define SDIZO_TREE

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

class binary_tree: public container_base 
{
	static constexpr int32_t REDUNDANT_SIZE = 10000; 

	BST_Node* root = nullptr; // pointer to data structure 
	
	int32_t elements = 0; // amount of elements inserted to heap
						  // points to free space just after last element
	// helper variables for tree printing
	std::string cr,cl,cp;
	// 
	bool is_ok = true;

public:
	binary_tree();
	binary_tree(std::initializer_list<int32_t> args_vector);
	~binary_tree();
  
  void load_from_file(std::string);

	void clear() override;

	bool find(int32_t key) override;

	// push key to heap
	void push_back(int32_t key) override;
  void push_back_DSW_free(int32_t key);
	
	// to save compatiblity with interface 
	bool insert(int32_t key, [[maybe_unused]]int32_t index = -1)override {
		this->push_back(key);
		return this->is_ok;
	};

	// remove element from heap by given value 
	bool remove(int32_t key) override;
  bool remove_DSW_free(int32_t key);

	void display() override;

  void perform_test(int32_t value, [[maybe_unused]]int32_t index ) override;
private:

	BST_Node* find_node(int32_t key);
	void display(std::string sp, std::string sn,BST_Node* node);
	
	void rotate_right(BST_Node* node);
	void rotate_left(BST_Node* node);
	BST_Node* tree_succesor(BST_Node*node);
	BST_Node* tree_predecessor(BST_Node*node);
	BST_Node* tree_maximum(BST_Node*node);
	BST_Node* tree_minimum(BST_Node*node);
	void tree_DSW();
	int32_t calculate_DSW_num(int32_t n);

};

#endif