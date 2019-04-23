#include "path_finding.h"
#include <random>
#include <time.h>
#include <iostream>
#include <iomanip>



void path_finding::load_from_file(std::string file_name){
  

  std::fstream fs (file_name, std::fstream::in | std::fstream::out);
  
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

void path_finding::generate_data(size_t vertex_count, size_t edge_count, int32_t begin_vertex){
  this->begin_vertex = begin_vertex;
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

void path_finding::push_back(Edge& e){
  // set new data in adjacency matrix
  this->a_matrix[e.v1][e.v2] = 1; 
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
  for (int i = 0; i < this->vertex_count; ++i)
    this->a_matrix[i] = new char [this->vertex_count]{0};

  // create new adjacency list
  this->a_list = new list<Edge>[vertex_count];
  // create list for result
  this->result = new list<Vertex>[vertex_count];
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

void path_finding::clear(){
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
  this->vertexes.clear();
}

void path_finding::perform_dijkstry(){
  using namespace std;
  // prepare priority queue
  Edge *item;
  // table for travel cost
  int32_t *v_weights       = new int32_t [this->vertex_count];
  // table for travel path     
  int32_t *v_parents       = new int32_t [this->vertex_count];
  int32_t *S       = new int32_t [this->vertex_count];
  bool    *visited_vertexs = new bool[this->vertex_count]{};
  
  int32_t i, u, j, sptr = 0;
  // cout << endl;
  for(int32_t i = 0; i < this->vertex_count; i++)
  {
    v_weights[i] = INT_MAX;
    v_parents[i] = -1;
    visited_vertexs[i] = false;
  }

  v_weights[this->begin_vertex] = 0;                       // Koszt dojścia v jest zerowy

  // Wyznaczamy ścieżki

  for(i = 0; i < this->vertex_count; i++)
  {
    // Szukamy wierzchołka w Q o najmniejszym koszcie d
    for(j = 0; visited_vertexs[j]; j++);
    for(u = j++; j < this->vertex_count; j++)
      if(!visited_vertexs[j] && (v_weights[j] < v_weights[u])) u = j;

    // Znaleziony wierzchołek przenosimy do S

    visited_vertexs[u] = true;

    // Modyfikujemy odpowiednio wszystkich sąsiadów u, którzy są w Q
    auto list_iterator = this->a_list[u].get_iter();
    while(true){
      item = list_iterator.get_and_next(); 
      if(!item)
        break;
       if(!visited_vertexs[item->v2] && (v_weights[item->v2] > v_weights[u] + item->w))
        {
          v_weights[item->v2] = v_weights[u] + item->w;
          v_parents[item->v2] = u;
        }
    }
  }

  // Gotowe, wyświetlamy wyniki
  for(i = 0; i < this->vertex_count; i++)
  {
    cout << i << ": ";

    // Ścieżkę przechodzimy od końca ku początkowi,
    // Zapisując na stosie kolejne wierzchołki

    for(j = i; j > -1; j = v_parents[j]) S[sptr++] = j;

    // Wyświetlamy ścieżkę, pobierając wierzchołki ze stosu

    while(sptr) cout << S[--sptr] << " ";

    // Na końcu ścieżki wypisujemy jej koszt

    cout << "$" << v_weights[i] << endl;
  }


}

void path_finding::perform_ford_belman(){

}

void path_finding::display_result(){
  using namespace std;
  // for(int32_t i = 0; i < this->vertex_count; i++)
  // {
  //   cout << "V[" << i << "] = ";
  //   this->result[i].display();
  //   cout << endl;
  // }
  // cout << endl << "MST Waga = " << this->total_weight << endl;
}

path_finding::~path_finding(){
  this->clear();
}  
