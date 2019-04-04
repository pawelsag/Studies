#ifndef SDIZO_RB_TREE
#define SDIZO_RB_TREE

#include "container_base.h"
#include "misc.h"
#include <initializer_list>
#include <algorithm>
#include <new>
#include <string>
#include <functional>

struct RBT_Node
{
  RBT_Node* up;
  RBT_Node* left;
  RBT_Node* right;
  int32_t key; // this variable is in the same time the key and our data 
  char color;
};

class red_black_tree: public container_base 
{
  static constexpr int32_t REDUNDANT_SIZE = 32; 

  RBT_Node* root = nullptr; // pointer to data structure 
  RBT_Node guard; // this item will prevent null dereferences

  int32_t elements = 0; // amount of elements inserted to heap
              // points to free space just after last element
  // helper variables for tree printing
  std::string cr,cl,cp;
  
  bool is_ok = true;

public:
  red_black_tree();
  red_black_tree(std::initializer_list<int32_t> args_vector);
  ~red_black_tree();

  void clear() override;

  bool find(int32_t key) override;

  // push key to heap
  void push_back(int32_t key) override;
  
  // to save compatiblity with interface 
  bool insert(int32_t key, [[maybe_unused]]int32_t index = -1) {
    this->push_back(key);
    return this->is_ok;
  };

  // remove element from heap by given value 
  bool remove(int32_t key) override;

  void display() override;

  void perform_test(std::fstream& write, int32_t population_size, int32_t* population =nullptr, int32_t* indexes =nullptr) override;
  
  void make_list(){
    RBT_Node *rotate_element = this->root;
    while(rotate_element != &this->guard){
      if(rotate_element->left != &this->guard){
        this->rotate_right(rotate_element);
        rotate_element = rotate_element->up;
      }else{
        rotate_element = rotate_element->right;
      }
    }
  }
private:

  RBT_Node* find_node(int32_t key);
  RBT_Node* tree_insert(int32_t key);
  void display(std::string sp, std::string sn,RBT_Node* node);
  
  void rotate_right(RBT_Node* node);
  void rotate_left(RBT_Node* node);
  RBT_Node* tree_succesor(RBT_Node*node);
  RBT_Node* tree_predecessor(RBT_Node*node);
  RBT_Node* tree_maximum(RBT_Node*node);
  RBT_Node* tree_minimum(RBT_Node*node);

};

#endif