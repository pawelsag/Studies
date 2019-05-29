#ifndef DISJOINT_SET
#define DISJOINT_SET

#include <stdint.h>
#include <cstdlib>
#include "common_struct.h"


class disjoint_set
{
	D_node* nodes;
	size_t size;
public:
	disjoint_set();

	explicit disjoint_set(uint32_t size);

	void operator=(const disjoint_set& l_value);

	~disjoint_set();

	void make_set();

	void make_set(D_node *v);

	D_node* find_set(int32_t vertex);

	D_node* find_set(D_node *vertex);

	void union_sets(Edge& e);

	void union_sets(D_node *val_1, D_node *val_2);

	void display();
  
  void clear(){
    this->make_set();
  }
};

#endif