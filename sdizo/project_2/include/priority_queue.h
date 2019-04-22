#ifndef PRIORITY_QUEUE_FILE
#define PRIORITY_QUEUE_FILE
#include "heap_template.h"

template <typename T>
class priority_queue : public binary_heap<T>
{

public:
  priority_queue()  =default;
  ~priority_queue() =default;
  
  T extract_top(){
    auto element = this->tab[0];
    this->remove(this->tab[0]);
    return element;
  }

  inline T maximum(){
    return this->tab[0];
  }
};

#endif