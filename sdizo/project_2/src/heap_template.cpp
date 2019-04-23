#include <iostream>

template<typename T>
binary_heap<T>::binary_heap(){
  this->size = binary_heap::REDUNDANT_SIZE;
  this->tab = new T[this->size];
  // variables used in printing
  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;

}
template<typename T>
binary_heap<T>::binary_heap(std::initializer_list<T> args_vector){
  
  for (auto&& val : args_vector){
    this->push_back(val);
  }
  // variables used in printing
  cr = cl = cp = "  ";
  cr[0] = 218; cr[1] = 196;
  cl[0] = 192; cl[1] = 196;
  cp[0] = 179;
}

template<typename T>
binary_heap<T>::~binary_heap(){
  delete [] this->tab;
}

template<typename T>
void binary_heap<T>::clear(){
  this->elements = 0;
  this->size = binary_heap::REDUNDANT_SIZE;
  delete [] this->tab;
  this->tab = new T[this->size];  
}

template<typename T>
bool binary_heap<T>::find(T value){
  if(this->find_index(value) == -1)
    return false;
  return true;
}

template<typename T>
int32_t binary_heap<T>::find_index(T key){
  // loop whole table and search for item
  for(int i =0; i < this->elements; i++)
    if(this->tab[i] == key)
      return i;
  return -1;
}


template<typename T>
void binary_heap<T>::push_back(T key){
  if(this->elements >= this->size){
    if( !this->realloc(MEMORY_OP::RESIZE_UP)){
      this->is_ok =false;
      return;
    }
  }
  // put child in heap
  this->tab[this->elements] = key;
  
  this->heap_up(this->elements);

  this->elements++;

  this->is_ok = true;

}

//move element from heap by given value 
template<typename T>
bool binary_heap<T>::remove(T key){
  if(this->elements < this->size - binary_heap::REDUNDANT_SIZE ){
    if( !this->realloc(MEMORY_OP::RESIZE_DOWN))
      return false;
  }

  int32_t key_idx = this->find_index(key);
  if(key_idx == -1) 
    return false;

  this->elements--;
  // swap found item with last element
  std::swap(this->tab[key_idx], this->tab[ this->elements ]);
  key = this->tab[key_idx];
  // if neccesary do heapify for lower elements 
  key_idx = this->heap_down(key_idx);
  // if neccesary do heapify for upper elements
  this->heap_up(key_idx);
  return true;
}


template<typename T>
void binary_heap<T>::display(std::string sp, std::string sn, int v){
  std::string s;

  if(v < this->elements)
  {
    s = sp;
    if(sn == cr) s[s.length() - 2] = ' ';
    this->display(s + cp, cr, this->right_child(v) );

    s = s.substr(0,sp.length()-2);

    std::cout << s << sn <<this->tab[v] << std::endl;

    s = sp;
    if(sn == cl) s[s.length() - 2] = ' ';
    this->display(s + cp, cl, this->left_child(v));
  }
}

template<typename T>
int32_t binary_heap<T>::heap_up(int32_t key_idx){
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
    key_idx = parent;
    parent =  this->parent(key_idx);
  }
  return key_idx;
}

template<typename T>
int32_t binary_heap<T>::heap_down(int32_t key_idx){
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
    // get new children
    l_child_idx = this->left_child(max_index);
    r_child_idx = this->right_child(max_index);
    key_idx =max_index;
  }
  return key_idx;
}

template<typename T>
void binary_heap<T>::display(){
  this->display("","", 0);
}