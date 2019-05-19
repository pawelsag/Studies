#ifndef PATH_FINDING_PROBLEMS
#define PATH_FINDING_PROBLEMS

#include "shortest_path_heap.h"
#include "list_template.h"
#include "common_struct.h"
#include <fstream>
#include <string>
#include <limits.h>

class path_finding
{
  char **a_matrix = nullptr;
  // create Adjacency list
  list<Edge> *a_list = nullptr;

  int32_t *v_parents = nullptr;
  int32_t *v_weights = nullptr;

  int32_t vertex_count = 0, edge_count =0, begin_vertex =0;

  size_t total_weight =0;
public:
  path_finding()  = default;
  ~path_finding();
  // this method appends new edge to not processed edges
  void push_back(Edge& e);
  void prepare_containers(size_t vertex_count, size_t edge_count);
  void load_from_file(std::string file_name);
  void generate_data(size_t vertex_count, size_t edge_count,int32_t begin_vertex);
  void display();
  void clear();
  void perform_dijkstry();
  void perform_ford_belman();

  void display_result();
private:
  // this method appends valid edge to internal data structure
  void append_edge([[maybe_unused]]Edge e){
  
  }

};

#endif