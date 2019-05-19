#ifndef SPH
#define SPH

#include "priority_queue.h"

template<typename T>
class shortest_path_heap : public priority_queue<T>
{
public:
  int *vertex_lookup;
  
  shortest_path_heap(){
    vertex_lookup = new int[1];
  }

  shortest_path_heap(size_t vertex_count){
    vertex_lookup = new int[vertex_count];
    // set index for each vertex
    for(size_t i =0 ; i < vertex_count; i++){
      vertex_lookup[i] = i;
    }  
  }

  ~shortest_path_heap(){
    delete [] vertex_lookup;
  }

  int32_t heap_up(int32_t key_idx){
          // get parent index
  int32_t parent = this->parent(key_idx);
  T key = this->tab[key_idx];
    // do heapify
  #ifdef HEAP_MIN
    while(key_idx > 0 && this->tab[parent] > key){
  #else
    while(key_idx > 0 && this->tab[parent] < key){
  #endif
      std::swap(this->tab[parent], this->tab[key_idx]);
      std::swap(this->vertex_lookup[this->tab[parent].v], this->vertex_lookup[this->tab[key_idx].v]);
      key_idx = parent;
      parent =  this->parent(key_idx);  
    }
    return key_idx;
  }

  int32_t heap_down(int32_t key_idx){
    int32_t l_child_idx, r_child_idx, max_index;
    T max_element;
    // get children
    l_child_idx = this->left_child(key_idx);
    r_child_idx = this->right_child(key_idx);

    // while index of currently handled child is bigger than last element index 
    while(l_child_idx < this->elements-1){
      
      // find smallest child
    #ifdef HEAP_MIN
      if(this->tab[l_child_idx] < this->tab[r_child_idx] || r_child_idx >= this->elements){
    #else
      if(this->tab[l_child_idx] > this->tab[r_child_idx] || r_child_idx >= this->elements){
    #endif
        max_element  = this->tab[l_child_idx];
        max_index = l_child_idx;
      }else{
        max_element = this->tab[r_child_idx];
        max_index = r_child_idx;      
      }
      // if child is smaller than currently handled element
      // stop heapifing
    #ifdef HEAP_MIN
      if(max_element > this->tab[key_idx])
        break;
    #else
      if(max_element < this->tab[key_idx])
        break;
    #endif
      // otherwise swap elements
      std::swap(this->tab[ key_idx ], this->tab[ max_index ]);
      std::swap(this->vertex_lookup[this->tab[max_index].v], this->vertex_lookup[this->tab[key_idx].v]);
      // get new children
      l_child_idx = this->left_child(max_index);
      r_child_idx = this->right_child(max_index);
      key_idx =max_index;
    }
    return key_idx;
  }

  bool remove(T key){
    if(this->elements < this->size - binary_heap<T>::REDUNDANT_SIZE ){
      if( !this->realloc(binary_heap<T>::MEMORY_OP::RESIZE_DOWN))
          return false;
      }

    int32_t key_idx = this->find_index(key);
    if(key_idx == -1) 
      return false;

    this->elements--;
    // swap found item with last element
    std::swap(this->tab[key_idx], this->tab[ this->elements ]);
    std::swap(this->vertex_lookup[this->tab[this->elements].v], this->vertex_lookup[this->tab[key_idx].v]);
    key = this->tab[key_idx];
    // if neccesary do heapify for lower elements 
    key_idx = this->heap_down(key_idx);
    // if neccesary do heapify for upper elements
    this->heap_up(key_idx);
    return true;
  }


  void display(){
    binary_heap<T>::display();

    for(int i = 0; i < this->elements; i++)
      std::cout<< i<<". "<<this->vertex_lookup[i] << "\n";   
  }

};


#endif