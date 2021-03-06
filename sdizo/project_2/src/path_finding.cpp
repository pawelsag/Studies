#include "path_finding.h"
#include <random>
#include <time.h>
#include <iostream>
#include <iomanip>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>


void path_finding::load_from_file(std::string file_name){
  
  this->last_opened_file = std::move(file_name);
  std::fstream fs (this->last_opened_file, std::fstream::in | std::fstream::out);
  
  if (!fs.is_open())
    return;

  Edge edge_tmp;
  // read size
  fs>>this->edge_count>> this->vertex_count >> this->begin_vertex;
  this->prepare_containers(vertex_count,edge_count);
  
  // read data from file until eof
  while( (edge_count--) ){
    // read vertwx begin, vertex end and weight
    fs >> edge_tmp.v1 >> edge_tmp.v2 >> edge_tmp.w;
    this->push_back(edge_tmp);
  }

  fs.close();
}

void path_finding::generate_data(size_t vertex_count, double edge_fullfilment, int32_t begin_vertex){
  // choose 2 of vertex_count
  // we need to fill our graph with edge_count edges 
  int64_t edge_count = (vertex_count*(vertex_count -1)) * edge_fullfilment;
  this->prepare_containers(vertex_count,edge_count);
  this->begin_vertex = begin_vertex;
  Edge edge_tmp;
  // generate tree
  for(int i = 0; i < this->vertex_count-1; ++i, edge_count--)
  {
    edge_tmp.v1 = i;
    edge_tmp.v2 = i+1;
    edge_tmp.w = rand() % 50 + 1;
    this->push_back(edge_tmp);
  }

  // create left edges
  while(edge_count > 0){
    edge_tmp.v1 = rand() % this->vertex_count;
    edge_tmp.v2 = rand() % this->vertex_count;
    edge_tmp.w  = rand() % 50 + 1;
    if( this->is_empty(edge_tmp) == false )
      continue;
    this->push_back(edge_tmp);
    edge_count--;
  }
}

void path_finding::push_back(Edge& e){
  // set new data in adjacency matrix
  this->a_matrix[e.v1][e.v2] = e.w; 
  // prepand new vertex to list 
  this->a_list[e.v1].push_back(e);
}


void path_finding::prepare_containers(size_t vertex_count, size_t edge_count){
  
  // release memory when necessary
  this->clear();

  this->vertex_count = vertex_count;
  this->edge_count = edge_count;
  
  //create new adjacency matrix
  this->a_matrix = new char*[this->vertex_count];
  this->a_matrix_backup = new char*[this->vertex_count];
  for (int i = 0; i < this->vertex_count; ++i){
    this->a_matrix[i] = new char [this->vertex_count]{0};
    this->a_matrix_backup[i] = new char [this->vertex_count]{0};
  }

  // create new adjacency list
  this->a_list = new list<Edge>[vertex_count];
  this->a_list_backup = new list<Edge>[vertex_count];

  // create list for result
  v_parents = new int32_t [this->vertex_count];
  v_weights = new int64_t [this->vertex_count];
}


void path_finding::clear(){
  // release memory when necessary
  if(this->a_matrix != nullptr){
    for (int i = 0; i < this->vertex_count; ++i){
      delete [] this->a_matrix[i];
      delete [] this->a_matrix_backup[i];
    }
    delete [] this->a_matrix;
    delete [] this->a_matrix_backup;
  }

  if( this->a_list != nullptr){
    delete [] this->a_list;
    delete [] this->a_list_backup;
  }
  

  if(this->v_parents != nullptr){
    delete [] this->v_parents;
    delete [] this->v_weights;
  }

  this->vertex_count =0;
  this->edge_count   =0;
  this->total_weight =0;
}

void path_finding::perform_dijkstry(){
  std::cout << "\nAdjacency matrix:\n"; 
  this->dijkstry_matrix();
  this->display_result();

  this->load_from_file(this->last_opened_file);

  std::cout << "\nAdjacency list:\n"; 
  this->dijkstry_list();
  this->display_result();
}
void path_finding::dijkstry_matrix(){
  // heap structure to efectivly extract smallest wieghts of elements
  shortest_path_heap<Vertex> vertexes(this->vertex_count);
  
  bool *visited_vertexs = new bool[this->vertex_count]{};
  
  int32_t i;
  char * matrix_row;
  Vertex v;
  // init all structers
  for(i = 0; i < this->vertex_count; i++)
  {
    this->v_parents[i] = -1;
    this->v_weights[i] = INT_MAX;
    visited_vertexs[i] = false;
    v.v = i;
    v.w = INT_MAX;
    vertexes.push_back(v);
  }
  // set begin vertex and update all structures
  this->v_weights[this->begin_vertex] = 0;
  v.v = this->begin_vertex;
  v.w = 0;

  vertexes.update_node(this->begin_vertex, v);
  visited_vertexs[this->begin_vertex] = true;

  // calculate all paths
  for(i = 0; i < this->vertex_count; i++)
  {
    auto min_vertex = vertexes.extract_top();

    visited_vertexs[min_vertex.v] = true;

    matrix_row = this->a_matrix[min_vertex.v];
    for(int j =0; j < this->vertex_count; j++){ 
      if(matrix_row[j] == 0)
        continue;
      if(!visited_vertexs[j] && (this->v_weights[j] > this->v_weights[min_vertex.v] + static_cast<int>(matrix_row[j]) )){
          this->v_weights[j] = v_weights[min_vertex.v] + static_cast<int>(matrix_row[j]);
          this->v_parents[j] = min_vertex.v;
          v.v = j;
          v.w = v_weights[j];
          vertexes.update_node(vertexes.vertex_lookup[j], v);
      }
    }
  }
}

void path_finding::dijkstry_list(){
  // heap structure to efectivly extract smallest wieghts of elements
  shortest_path_heap<Vertex> vertexes(this->vertex_count);
  
  bool *visited_vertexs = new bool[this->vertex_count]{};
  
  int32_t i;
  Edge *item;
  Vertex v;
  // init all structers
  for(i = 0; i < this->vertex_count; i++)
  {
    v_parents[i] = -1;
    v_weights[i] = INT_MAX;
    visited_vertexs[i] = false;
    v.v = i;
    v.w = INT_MAX;
    vertexes.push_back(v);
  }
  // set begin vertex and update all structures
  v_weights[this->begin_vertex] = 0;
  v.v = this->begin_vertex;
  v.w = 0;

  vertexes.update_node(this->begin_vertex, v);
  visited_vertexs[this->begin_vertex] = true;

  // calculate all paths
  for(i = 0; i < this->vertex_count; i++)
  {
    auto min_vertex = vertexes.extract_top();

    visited_vertexs[min_vertex.v] = true;

    auto list_iterator = this->a_list[min_vertex.v].get_iter();
    while(true){
      item = list_iterator.get_and_next(); 
      if(!item)
        break;
      if(!visited_vertexs[item->v2] && (v_weights[item->v2] > v_weights[min_vertex.v] + item->w)){
          v_weights[item->v2] = v_weights[min_vertex.v] + item->w;
          v_parents[item->v2] = min_vertex.v;
          v.v = item->v2;
          v.w = v_weights[item->v2];
          vertexes.update_node(vertexes.vertex_lookup[item->v2], v);
      }
    }
  }
}


void path_finding::perform_ford_belman(){
  std::cout << "\nAdjacency matrix:\n"; 
  this->ford_belman_matrix();
  this->display_result();

  this->load_from_file(this->last_opened_file);

  std::cout << "\nAdjacency list:\n"; 
  this->ford_belman_list();
  this->display_result();
}

void path_finding::ford_belman_list(){
  int32_t i;
  Edge *item;
  bool path_changed;
  // init all structers
  for(i = 0; i < this->vertex_count; i++)
  {
    v_parents[i] = -1;
    v_weights[i] = INT_MAX;
  }

  v_weights[this->begin_vertex] = 0;

  for(int i =1; i < this->vertex_count; i++){
    path_changed = false;
    for(int x =0; x < this->vertex_count; x++){
      auto list_iterator = this->a_list[x].get_iter();
      while( true ){
        item = list_iterator.get_and_next(); 
        if(!item)
          break;
        if(v_weights[x] + item->w < v_weights[item->v2]){
          path_changed = true;
          v_weights[item->v2] = v_weights[x] + item->w;
          v_parents[item->v2] = x;
        }
      }
    }
    if(path_changed == false)
      return;
  }

  bool is_correct = true;

  for(int x = 0; x < this->vertex_count; ++x){
    auto list_iterator = this->a_list[x].get_iter();
    while( true ){
      item = list_iterator.get_and_next(); 
      if(!item)
        break;
      if(v_weights[x] + item->w < v_weights[item->v2])
        is_correct = false;
      break;
    }
  }
  assert(is_correct);
}

void path_finding::ford_belman_matrix(){
  int32_t i;
  bool path_changed;
  // init all structers
  for(i = 0; i < this->vertex_count; i++)
  {
    v_parents[i] = -1;
    v_weights[i] = INT_MAX;
  }

  v_weights[this->begin_vertex] = 0;

  for(int i =1; i < this->vertex_count; i++){
    path_changed = false;
    for(int x =0; x < this->vertex_count; x++){
      for( int j =0 ; j < this->vertex_count; j++ ){ 
        if( this->a_matrix[x][j] == 0 )
          continue;
        if(v_weights[x] + this->a_matrix[x][j] < v_weights[j]){
          path_changed = true;
          v_weights[j] = v_weights[x] + this->a_matrix[x][j];
          v_parents[j] = x;
        }
      }
    }
    if(path_changed == false)
      return;
  }

  bool is_correct = true;

  for(int x = 0; x < this->vertex_count; ++x){
    for( int j =0 ; j < this->vertex_count; j++ ){
      if(this->a_matrix[x][j] == 0)
        continue;
      if(v_weights[x] + this->a_matrix[x][j] < v_weights[j])
        is_correct = false;
      break;
    }
  }
  assert(is_correct);
}

void path_finding::display(){
  using namespace std;
  int32_t i, j;

  std::cout << "   ";
  for(i = 0; i < this->vertex_count; i++) cout << setw(3) << i;
  cout<<"\n";
  // display adjacency matrix
  for(i = 0 ;i < this->vertex_count; i++){
    std::cout << setw(3) << i;
    for(j = 0 ;j < this->vertex_count; j++)
      std::cout << setw(3) << (int) this->a_matrix[i][j];
    std::cout << std::endl;
  }

  // display adjacency list
  for(i = 0; i < this->vertex_count; i++){
    cout << "V[" << i << "] = ";
    this->a_list[i].display();
    cout << endl;
  }

}

void path_finding::display_result(){

  int32_t *S = new int32_t [this->vertex_count];
  int32_t sptr = 0;
  // show result
  for(int i = 0; i < this->vertex_count; i++)
  {
    std::cout << i << ": ";
    // reverse path to put vertexes in correct order
    for(int j = i; j > -1; j = v_parents[j]) S[sptr++] = j;
    // pop from stack and show
    while(sptr) std::cout << S[--sptr] << " ";
    // show total cost of path
    std::cout << " Koszt: " << v_weights[i] << "\n";
  }
}

path_finding::~path_finding(){
  this->clear();
}  
