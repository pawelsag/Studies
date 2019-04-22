#ifndef MST_AREA
#define MST_AREA

#include "disjoint_set.h"
#include "priority_queue.h"
#include "list_template.h"
#include "common_struct.h"
#include <fstream>
#include <string>

class MST
{
  disjoint_set unions;
  priority_queue<Edge> edges;

  // create Adjacency matrix
  char **a_matrix = nullptr;
  // create Adjacency list
  list<int32_t> *a_list = nullptr;
  // create list for processed data
  list<Edge> *result = nullptr;

  int32_t vertex_count, edge_count;

  size_t total_weight;

public:
  MST()  = default;
  ~MST();
  // this method appends new edge to not processed edges
  void push_back(Edge& e);
  void prepare_containers(size_t vertex_count, size_t edge_count);
  void load_from_file(std::string file_name);
  void generate_data(size_t vertex_count, size_t edge_count);
  void display();
  void clear();
  void perform_kruskal();

  void display_result();
private:
  // this method appends valid edge to internal data structure
  void append_edge(Edge& e){
    this->result[e.v1].push_back(e);
    std::swap(e.v1, e.v2);
    this->result[e.v1].push_back(e);
    
    this->total_weight += e.w;
  }

};

#endif