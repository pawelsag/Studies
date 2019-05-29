#ifndef MST_AREA
#define MST_AREA

#include "disjoint_set.h"
#include "priority_queue.h"
#include "list_template.h"
#include "common_struct.h"
#include <fstream>
#include <string>
#include <random>
#include <time.h>
class graph_tester;

class MST
{
  friend graph_tester;

  disjoint_set unions;
  priority_queue<Edge> edges;

  // create Adjacency list
  list<Edge> *a_list = nullptr;
  // create list for processed data
  list<Edge> *result = nullptr;

  // create Adjacency matrix
  char **a_matrix = nullptr;  
  char **a_matrix_backup = nullptr;  
  // create Adjacency list
  list<Edge> *a_list_backup = nullptr;

  int32_t vertex_count = 0, edge_count =0;

  size_t total_weight =0;

  std::string last_opened_file;

public:
  MST()  { srand(time(0)); }
  ~MST();
  // this method appends new edge to not processed edges
  void push_back(Edge& e);
  void prepare_containers(size_t vertex_count, size_t edge_count);
  void load_from_file(std::string file_name);
  void generate_data(size_t vertex_count, double edge_fullfilment);
  void display();
  void clear();
  void perform_kruskal();
  void perform_prim();

  void display_result();
  
  void save_state(){
    for(int i =0 ; i < this->vertex_count; i++){
      this->a_list_backup[i] = this->a_list[i];
      for(int j =0 ; j < this->vertex_count; j++)
        this->a_matrix_backup[i][j] = this->a_matrix[i][j];
    }
  }
  
  void restore_state(){
    this->unions.clear();
    for(int i =0 ; i < this->vertex_count; i++){
      this->a_list[i].clear();
      this->a_list[i] = this->a_list_backup[i];
      for(int j =0 ; j < this->vertex_count; j++)
        this->a_matrix[i][j] = this->a_matrix_backup[i][j];
    }
  }

private:
  // this method appends valid edge to internal data structure
  void append_edge(Edge e){
    this->result[e.v1].push_back(e);
    std::swap(e.v1, e.v2);
    this->result[e.v1].push_back(e);
    this->total_weight += e.w;
  }

  bool is_empty(Edge e){
    return this->a_matrix[e.v1][e.v2] == 0;
  }

  void kruskal_append_result();
  void prime_append_result();

  void kruskal_list();
  void kruskal_matrix();
  void prime_list();
  void prime_matrix();
};

#endif