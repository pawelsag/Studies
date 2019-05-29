#include "test_module.h"
#include <fstream>
#include <random>
#include <chrono>
#include <cstring>
void graph_tester::run_test(){
  // chrono measure variables
  using namespace std;
  using namespace std::chrono;
  high_resolution_clock::time_point t1;
  high_resolution_clock::time_point t2;
  double results[4];

  const char *header = "Liczba wierzcholkow;Wypelnienie wierzcholkow;Typ algorytmu;Srednia";
  const char *format_str = "%i;%f;%s;%f\n";
  char buff[1000];

  std::fstream fs ("mst_test.txt", std::fstream::out);
  srand(time(0));

  if (!fs.is_open())
    return;

  fs << header;

  for(auto count : vertex_count){
    for(auto fullfilment : graph_fulfillment){
        std::memset(results, 0, sizeof results);
        std::cout<< "V:" << count << "; f:"<<fullfilment <<std::endl;
        for(int i =0 ; i < 100; i++){
          mst_instance.generate_data(count, fullfilment);     
          mst_instance.save_state();
          std::cout << "kruskal_list"<<std::endl;
          t1 = high_resolution_clock::now();  
          mst_instance.kruskal_list();
          t2 = high_resolution_clock::now();
          results[0] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

          mst_instance.restore_state();
          std::cout << "kruskal_matrix"<<std::endl;
          t1 = high_resolution_clock::now();            
          mst_instance.kruskal_matrix();   
          t2 = high_resolution_clock::now();
          results[1] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
            
          std::cout << "prime_list"<<std::endl;
          mst_instance.restore_state();  
          t1 = high_resolution_clock::now();            
          mst_instance.prime_list();   
          t2 = high_resolution_clock::now();
          results[2] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
          
          mst_instance.restore_state();  
          std::cout << "prime_matrix"<<std::endl;
          t1 = high_resolution_clock::now();            
          mst_instance.prime_matrix();   
          t2 = high_resolution_clock::now();
          results[3] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
          mst_instance.restore_state();
      }
      sprintf(buff, format_str, count,fullfilment,"kruskal_list",results[0]/100);
      fs << buff;
      sprintf(buff, format_str, count,fullfilment,"kruskal_matrix",results[1]/100);
      fs << buff;
      sprintf(buff, format_str, count,fullfilment,"prime_list",results[2]/100);
      fs << buff;
      sprintf(buff, format_str, count,fullfilment,"prime_matrix",results[3]/100);
      fs << buff;
    }
  }
  
  fs.close();

  fs.open("pf_test.txt", std::fstream::out);
  int begin_vertex;

  if (!fs.is_open())
    return;
  fs << header;
  for(auto count : vertex_count){
    for(auto fullfilment : graph_fulfillment){
      std::memset(results, 0, sizeof results);
      for(int i =0 ; i < 100; i++){
        begin_vertex = rand()%count; 
        pf_instance.generate_data(count, fullfilment,begin_vertex);     
        pf_instance.save_state();

        t1 = high_resolution_clock::now();  
        pf_instance.dijkstry_list();
        t2 = high_resolution_clock::now();
        results[0] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();

        pf_instance.restore_state();

        t1 = high_resolution_clock::now();            
        pf_instance.dijkstry_matrix();   
        t2 = high_resolution_clock::now();
        results[1] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        
        pf_instance.restore_state();

        t1 = high_resolution_clock::now();            
        pf_instance.ford_belman_list();  
        t2 = high_resolution_clock::now();
        results[2] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        
        pf_instance.restore_state();

        t1 = high_resolution_clock::now();            
        pf_instance.ford_belman_matrix();   
        t2 = high_resolution_clock::now();
        results[3] += chrono::duration_cast<chrono::nanoseconds>(t2 - t1).count();
        pf_instance.restore_state();
      }

      sprintf(buff, format_str, count, fullfilment, "dijkstry_list", results[0]/100);
      fs << buff;
      sprintf(buff, format_str, count, fullfilment, "dijkstry_matrix", results[1]/100);
      fs << buff;
      sprintf(buff, format_str, count, fullfilment, "ford_belman_list", results[2]/100);
      fs << buff;
      sprintf(buff, format_str, count, fullfilment, "ford_belman_matrix", results[3]/100);
      fs << buff;
    }
  }

  fs.close();
}