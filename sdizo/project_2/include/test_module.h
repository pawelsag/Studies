#ifndef TEST_MODULE
#define TEST_MODULE

#include "MST.h"
#include "path_finding.h"

class graph_tester{

private:
  MST mst_instance; 
  path_finding pf_instance; 

public:
  const int32_t vertex_count[5] = {30,40,50,60,70};
  const double graph_fulfillment[4] = {0.25f, 0.50f, 0.75f, 0.99f};
  void run_test();

};

#endif