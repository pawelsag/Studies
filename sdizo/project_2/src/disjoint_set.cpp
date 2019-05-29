#include "disjoint_set.h"
disjoint_set::disjoint_set(){
  this->nodes = new D_node[1];
  this->size = 1;
  this->make_set();
}

disjoint_set::disjoint_set(uint32_t size){
  nodes = new D_node[size];
  this->size = size;
  this->make_set();
}

void disjoint_set::operator=(const disjoint_set& l_value){
  this->nodes = new D_node[l_value.size];
  this->size = l_value.size;
  for(uint32_t i =0 ; i < l_value.size ; i++){
    this->nodes[i].parent = &this->nodes[i];
    this->nodes[i].rank   = l_value.nodes[i].rank;
    this->nodes[i].vertex = l_value.nodes[i].vertex;
  } 
}

void disjoint_set::display(){
  using namespace std;
  for(uint32_t i =0; i < this->size; i++){
    cout << "Parent: "<<  this->nodes[i].parent<<endl;
    cout << "Rank: "  <<  this->nodes[i].rank<<endl;
    cout << "Vertex: "<<  this->nodes[i].vertex<<endl;
  }
}

disjoint_set::~disjoint_set(){
  delete [] nodes;  
}

void disjoint_set::make_set(){
  for(uint32_t i=0; i < this->size;i++){
    this->nodes[i].parent = &this->nodes[i];
    this->nodes[i].rank = 0;
    this->nodes[i].vertex = i;
  }
}

void disjoint_set::make_set(D_node *v){
  this->nodes[v->vertex].parent = v;
  this->nodes[v->vertex].rank = 0;
  this->nodes[v->vertex].vertex = v->vertex;
}

D_node* disjoint_set::find_set(int32_t vertex){
  return this->find_set(&this->nodes[vertex]);
}

D_node* disjoint_set::find_set(D_node *vertex){
  if( vertex->parent != vertex ) vertex->parent = this->find_set(vertex->parent);
  return vertex->parent;
}

void disjoint_set::union_sets(Edge& e)
{
  this->union_sets(&this->nodes[e.v1], &this->nodes[e.v2]);   
}

void disjoint_set::union_sets(D_node *val_1, D_node *val_2)
{
  D_node *first_union_root,*second_union_root;

  first_union_root = this->find_set(val_1);
  second_union_root = this->find_set(val_2);

  if(first_union_root != second_union_root)           
  {
    if(first_union_root->rank > second_union_root->rank)
       second_union_root->parent = first_union_root;       
    else
    {
      first_union_root->parent = second_union_root;
      if(first_union_root->rank == second_union_root->rank) second_union_root->rank++;
    }
  }
}