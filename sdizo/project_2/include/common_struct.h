#ifndef COMMON_STRUCTURES
#define COMMON_STRUCTURES
#include <stdint.h>
#include <iostream>

// internal list structrue
template<typename F>
  struct node{
    node* next = nullptr;
    node* prev = nullptr;
    F value = {}; 
  };

// structer holds data necessary to create disjoint set
struct D_node{
  D_node  *parent;
  int32_t rank;
  int32_t vertex;
};

// neighbourhood list
struct N_list
{
  N_list * next;
  int v,w;
  
  bool operator<(N_list& rhs){
    return w < rhs.w;
  }

  bool operator<=(N_list& rhs){
    return w < rhs.w;
  }

  bool operator>(N_list& rhs){
    return w > rhs.w;
  }

  bool operator>=(N_list& rhs){
    return w >= rhs.w;
  }

  bool operator==(N_list& rhs){
    return v == rhs.v;
  }

  friend std::ostream& operator<<(std::ostream& os, N_list& rhs){
    os << rhs.v << rhs.w;
    return os;
  }

};

// typical graph connection struct
// vertexes + weight of the edge 
struct Edge
{
  int v1, v2, w;

  bool operator<(Edge& rhs){
    return w < rhs.w;
  }

  bool operator<=(Edge& rhs){
    return w < rhs.w;
  }

  bool operator>(Edge& rhs){
    return w > rhs.w;
  }

  bool operator>=(Edge& rhs){
    return w >= rhs.w;
  }

  bool operator==(Edge& rhs){
    return w == rhs.w;
  }

  template<typename T,
           typename = typename std::enable_if_t<
                               std::is_same<typename std::decay<T>::type, Edge>::value>::type
          >
  Edge& operator=(T&& rhs){
      v1 = rhs.v1;
      v2 = rhs.v2;
      w = rhs.w;
      return *this;
  }

  friend std::ostream& operator<<(std::ostream& os, Edge& rhs){
    os << rhs.v2;
    return os;
  }
   
};

#endif