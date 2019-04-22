#include "MST.h"
#include <random>
#include <time.h>
#include <iostream>
#include <iomanip>



void MST::load_from_file(std::string file_name){
  

  std::fstream fs (file_name, std::fstream::in | std::fstream::out);
  
  if (!fs.is_open())
    return;

  int vertex_count, edge_count;
  Edge edge_tmp;
  // read size
  fs>>edge_count>>vertex_count;
  this->prepare_containers(vertex_count,edge_count);
  
  // read data from file until eof
  while( (edge_count--) ){
    // read vertwx begin, vertex end and weight
    fs >> edge_tmp.v1 >> edge_tmp.v2 >> edge_tmp.w;
    this->push_back(edge_tmp);
  }

  fs.close();
}

void MST::generate_data(size_t vertex_count, size_t edge_count){
  this->prepare_containers(vertex_count,edge_count);
  Edge edge_tmp;
  // read data from file until eof
  srand(time(0));
  while( (edge_count--) ){
    // read vertwx begin, vertex end and weight
    do{
      edge_tmp.v1 = rand() % vertex_count;
      edge_tmp.v2 = rand() % vertex_count; 
    }while(edge_tmp.v1 == edge_tmp.v2);
    edge_tmp.w = rand() % 0xabcd;    
    this->push_back(edge_tmp);
  }
}

void MST::push_back(Edge& e){
  // set new data in adjacency matrix
  this->a_matrix[e.v1][e.v2] = 1; 
  // prepand new vertex to list 
  this->a_list[e.v1].push_back(e);
  std::swap(e.v1, e.v2);
  // cause our graph is undirected
  // we should perform simmetric append
  this->a_matrix[e.v1][e.v2] = 1; 
  this->a_list[e.v1].push_back(e);
}


void MST::prepare_containers(size_t vertex_count, size_t edge_count){
  
  // release memory when necessary
  this->clear();

  this->vertex_count = vertex_count;
  this->edge_count = edge_count;

  //create new adjacency matrix
  this->a_matrix = new char*[this->vertex_count];
  for (int i = 0; i < this->vertex_count; ++i)
    this->a_matrix[i] = new char [this->vertex_count]{0};

  // create new adjacency list
  this->a_list = new list<Edge>[vertex_count];
  // create list for result
  this->result = new list<Edge>[vertex_count];
  // create new set
  this->unions = disjoint_set(vertex_count);
}

void MST::display(){
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

void MST::clear(){
  // release memory when necessary
  if(this->a_matrix != nullptr){
    for (int i = 0; i < this->vertex_count; ++i)
      delete [] this->a_matrix[i];
    delete [] this->a_matrix;
  }

  if( this->a_list != nullptr)
    delete [] this->a_list;

  if(this->result != nullptr)
    delete [] this->result;

  this->vertex_count =0;
  this->edge_count =0;
  this->total_weight =0;
  this->edges.clear();
}

void MST::perform_kruskal(){
  // prepare priority queue
  Edge *item;
  for(int32_t i = 0; i < this->vertex_count; i++){
    auto list_iterator = this->a_list[i].get_iter();
    while(true){
        item = list_iterator.get_and_next();
        if(!item)
          break;
        this->edges.push_back(*item);
    }
  }

  // perform algorithm
  Edge e;
  for(int32_t i = 1; i < this->vertex_count; i++)          
  {
    do{
      e = this->edges.extract_top();                     
    }while(this->unions.find_set(e.v1) == this->unions.find_set(e.v2));
    this->append_edge(e);               
    this->unions.union_sets(e);
  }
}

void MST::perform_prim(){
    bool *visited_vertexs = new bool[this->vertex_count]{false};
    Edge *item, e;

    auto list_iterator = this->a_list[0].get_iter();
    visited_vertexs[0] = true;
    // append all edges which connect with given vertex
    
    for(int32_t i = 1; i < this->vertex_count; i++)          
    {

      while(true){
        item = list_iterator.get_and_next();
        if(!item)
          break;
        if(visited_vertexs[item->v2])
          continue;
        this->edges.push_back(*item);
      }

      do{
        e = this->edges.extract_top();
      }while(this->unions.find_set(e.v1) == this->unions.find_set(e.v2));
      this->append_edge(e);
      this->unions.union_sets(e);

      list_iterator = this->a_list[e.v2].get_iter();                      
      visited_vertexs[e.v2] = true;
           
    }

    delete [] visited_vertexs;
}

void MST::display_result(){
  using namespace std;
  for(int32_t i = 0; i < this->vertex_count; i++)
  {
    cout << "V[" << i << "] = ";
    this->result[i].display();
    cout << endl;
  }
  cout << endl << "MST Waga = " << this->total_weight << endl;
}

MST::~MST(){
  this->clear();
}  
