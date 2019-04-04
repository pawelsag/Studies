#include "red_black_tree.h"
#include <iostream>
#include <string>
#include <new>
#include <chrono>
red_black_tree::red_black_tree(){

  // variables used in printing
  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
  // init guard
  this->guard.color = 'B';          
  this->guard.up    = &this->guard;
  this->guard.left  = &this->guard;
  this->guard.right = &this->guard;
  this->guard.key   = -1;
  this->root        = &this->guard;
}

red_black_tree::red_black_tree(std::initializer_list<int32_t> args_vector){
  
  // variables used in printing
  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
  // init guard
  this->guard.color = 'B';          
  this->guard.up    = &this->guard;
  this->guard.left  = &this->guard;
  this->guard.right = &this->guard;
  this->guard.key   = -1;
  this->root        = &this->guard;

  for (auto&& val : args_vector){
    this->push_back(val);
  }
}

red_black_tree::~red_black_tree(){
  this->clear();
}

bool red_black_tree::find(int32_t value){
  if(this->find_node(value) == nullptr)
    return false;
  return true;
} 

void red_black_tree::clear(){
  RBT_Node *rotate_element = this->root;
  // expand binary structure to straight line 
  while(rotate_element != &this->guard){
    if(rotate_element->left != &this->guard){
      this->rotate_left(rotate_element);
      rotate_element = rotate_element->up;
    }else{
      rotate_element = rotate_element->right;
    }
  }
  rotate_element = this->root;
  // delete all nodes from structure
  while(rotate_element != &this->guard){
    this->root = rotate_element->right; 
    delete rotate_element;
    rotate_element = this->root;
  }
  this->elements =0;
}

RBT_Node* red_black_tree::find_node(int32_t key){
  RBT_Node *node = this->root ;
  while( node != &this->guard && node->key != key ){
    if( node->key < key)
      node = node->right;
    else
      node = node->left;
  }
  return node;
}

RBT_Node* red_black_tree::tree_insert(int32_t key){
  RBT_Node *new_node;
  try{
    new_node = new RBT_Node;
  }catch(const std::bad_alloc& e){
    is_ok = false;
    return &this->guard;
  }
  new_node->left = &this->guard;
  new_node->right = &this->guard;
  new_node->key = key;

  RBT_Node* top = this->root, *parent = &this->guard;

  while(top != &this->guard){
    parent = top;
    if (new_node->key < top->key)
      top = top->left;
    else
      top = top->right;
  }

  new_node->up = parent;
  if(parent == &this->guard){
    this->root = new_node;
  }else if(new_node->key < parent->key)
    parent->left = new_node;
  else
    parent->right = new_node;

  this->elements++;
  this->is_ok = true;
  return new_node;
}

void red_black_tree::push_back(int32_t key){
  RBT_Node *inserted_node = this->tree_insert(key);
  RBT_Node *uncle;
  inserted_node->color = 'R';

  while(inserted_node != this->root && inserted_node->up->color == 'R'){
    if(inserted_node->up == inserted_node->up->up->left){
      uncle = inserted_node->up->up->right;
      if(uncle->color == 'R'){
        inserted_node->up->color = 'B';
        uncle->color = 'B';
        uncle->up->color = 'R';
        inserted_node = inserted_node->up->up;       
        continue;
      }
      
      if(inserted_node == inserted_node->up->right){
        inserted_node = inserted_node->up;
        this->rotate_left(inserted_node);
      }
      inserted_node->up->color = 'B';
      inserted_node->up->up->color = 'R';
      this->rotate_right(inserted_node->up->up);
    }else{
      uncle = inserted_node->up->up->left;
      if(uncle->color == 'R'){
        inserted_node->up->color = 'B';
        uncle->color = 'B';
        uncle->up->color = 'R';
        inserted_node = inserted_node->up->up;       
        continue;
      }
      
      if(inserted_node == inserted_node->up->left){
        inserted_node = inserted_node->up;
        this->rotate_right(inserted_node);
      }
      inserted_node->up->color = 'B';
      inserted_node->up->up->color = 'R';
      this->rotate_left(inserted_node->up->up);    
    }
  }
  
  this->root->color = 'B';
}


bool red_black_tree::remove(int32_t key){
  RBT_Node *node = this->find_node(key);
  if(node == nullptr)
    return false;

  RBT_Node *node_to_remove, *child;
  
  // if node has at most one child
  if(node->left == nullptr || node->right == nullptr)
    node_to_remove = node;
  else // node has more than one child
    // find successor of current  child 
    node_to_remove = this->tree_succesor(node);

  // find child of removing node
  // the only possible scenario here is that 
  // node can have at most one child
  if(node_to_remove->left)
    child = node_to_remove->left;
  else
    child = node_to_remove->right;
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
  
  return true;
}

void red_black_tree::display(std::string sp, std::string sn,RBT_Node* node){
  using namespace std;
  string s;
  
  if(node != &this->guard)
  {    

    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    this->display(s + cp, cr, node->right);

    s = s.substr(0,sp.length()-2);
    if(node->color == 'R')
      cout << s << sn <<text_colors::red<< node->key << text_colors::white << endl;
    else
      cout << s << sn << node->key << endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    this->display(s + cp, cl, node->left);
  }
}

void red_black_tree::rotate_right(RBT_Node* A){
  
  RBT_Node *parent, *B;
  parent = A->up;
  // store A left element
  B = A->left;
  // it means that node do not have elements on his left 
  if(B != &this->guard){
    // store B right element
    A->left = B->right;
    // if current left element of A is not null
    // assign new parent
    if(A->left) A->left->up = A;
    // assign new right element
    B->right = A;
    B->up = parent;
    A->up = B;
    if(parent != &this->guard){
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

void red_black_tree::rotate_left(RBT_Node* A){
 
  RBT_Node *parent, *B;
  parent = A->up;
  // store A right element
  B = A->right;
  // it means that node do not have elements on his left 
  if(B != &this->guard){
    // store B left element
    A->right = B->left;
    // if current right element of A is not null
    // assign new parent
    if(A->right) A->right->up = A;
    // assign new left element
    B->left = A;
    B->up = parent;
    A->up = B;
    if(parent != &this->guard){
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

RBT_Node* red_black_tree::tree_succesor(RBT_Node*node){
  if(node->right != &this->guard)
    return this->tree_minimum(node->right);

  RBT_Node* succesor = node->up;
  while(succesor != &this->guard && succesor->right == node){
    node = succesor;
    succesor = succesor->up;
  }
  return succesor;
}
RBT_Node* red_black_tree::tree_predecessor(RBT_Node*node){
  if(node->left != &this->guard)
    return this->tree_maximum(node->left);

  RBT_Node *succesor = node->up;
  while(succesor != &this->guard&& succesor->left == node){
    node = succesor;
    succesor = succesor->up;
  }
  return succesor;  
}

RBT_Node* red_black_tree::tree_maximum(RBT_Node*node){
  RBT_Node *max_node = node;
  while(max_node->right != &this->guard)
    max_node = max_node->right;
  return max_node;
}

RBT_Node* red_black_tree::tree_minimum(RBT_Node*node){
  RBT_Node *min_node = node;
  while(min_node->left != &this->guard)
    min_node = min_node->left;
  return min_node;
}


void red_black_tree::display(){
  this->display("","", this->root);
}

void red_black_tree::perform_test(std::fstream& write, int32_t population_size, int32_t* population, int32_t* indexes ){
  using namespace std;
  using namespace std::chrono;
  // chrono measure variables
  duration<double> time_span;
  high_resolution_clock::time_point t1;
  high_resolution_clock::time_point t2;
      

  // push back test;
    std::cout << "Dodanie  " << population_size <<" wartosci"<<endl;
  t1 = high_resolution_clock::now();
  for (int32_t j = 0; j < population_size ; ++j)
  {
    this->push_back(population[j]); 
  }   
  t2 = high_resolution_clock::now();

  time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " sekund.";
  std::cout << std::endl;
  // save result in file
  write <<time_span.count() <<";";
  

  // search test;
    std::cout << "Wyszukiwanie "<<population_size << " wartosci sposrod " << population_size <<" egzemplarzy"<<endl;
  t1 = high_resolution_clock::now();
  for (int32_t j = 0; j < population_size ; ++j)
  {
    this->find(population[indexes[j]]); 
  }   
  t2 = high_resolution_clock::now();

  time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " sekund.";
  std::cout << std::endl;
  
  // save result in file
  write <<time_span.count() <<";";
  

  
  // random delete test;
    std::cout << "Usuwanie losowe " << population_size <<" wartosci"<<endl;
  t1 = high_resolution_clock::now();
  for (int32_t j = 0; j < population_size; ++j)
  {
    this->remove(population[j]); 
  }   
  t2 = high_resolution_clock::now();

  time_span = duration_cast<duration<double>>(t2 - t1);

  std::cout << "Zajelo :" << time_span.count() << " sekund.";
  std::cout << std::endl;
  // save result in file
  write <<time_span.count() <<";";

  write << population_size<<endl;
}