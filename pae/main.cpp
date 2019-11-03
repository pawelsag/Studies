#include <internals.hpp>
#include <path_manager.hpp>
#include <precise_algorithms.hpp>
#include <precise_algorithms_test.hpp>
int
main(int argc, char const* argv[])
{
 
  TSP::TEST::precise_algorithms_tester test;
  test.run();

  return 0;
}