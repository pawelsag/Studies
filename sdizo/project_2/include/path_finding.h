#ifndef PATH_FINDING_PROBLEMS
#define PATH_FINDING_PROBLEMS

#include "shortest_path_heap.h"
#include "list_template.h"
#include "common_struct.h"
#include <fstream>
#include <string>
#include <limits.h>
#include <random>
#include <time.h>

class graph_tester;

class path_finding
{
  friend graph_tester;

  char **a_matrix = nullptr;
  char **a_matrix_backup = nullptr;

  // create Adjacency list
  list<Edge> *a_list = nullptr;
  list<Edge> *a_list_backup = nullptr;

  int32_t *v_parents = nullptr;
  int64_t *v_weights = nullptr;

  int32_t vertex_count = 0, edge_count =0, begin_vertex =0;

  size_t total_weight =0;
  std::string last_opened_file;
public:
  path_finding(){
    srand( time(0) );
  }
  ~path_finding();
  // this method appends new edge to not processed edges
  void push_back(Edge& e);
  void prepare_containers(size_t vertex_count, size_t edge_count);
  void load_from_file(std::string file_name);
  void generate_data(size_t vertex_count, double edge_fullfilment, int32_t begin_vertex);
  void display();
  void clear();
  void perform_dijkstry();
  void perform_ford_belman();
  void display_result();

  void save_state(){
    for(int i =0 ; i < this->vertex_count; i++){
      this->a_list_backup[i] = this->a_list[i];
      for(int j =0 ; j < this->vertex_count; j++)
        this->a_matrix_backup[i][j] = this->a_matrix[i][j];
    }
  }
  
  void restore_state(){
    for(int i =0 ; i < this->vertex_count; i++){
      this->a_list[i].clear();
      this->a_list[i] = this->a_list_backup[i];
      for(int j =0 ; j < this->vertex_count; j++)
        this->a_matrix[i][j] = this->a_matrix_backup[i][j];
    }
  }

private:
  bool is_empty(Edge e){
    return this->a_matrix[e.v1][e.v2] == 0;
  }

  void dijkstry_matrix();
  void dijkstry_list();
  void ford_belman_matrix();
  void ford_belman_list();
};

#endif