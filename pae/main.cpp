#include <internals.hpp>
#include <path_manager.hpp>
#include <precise_algorithms.hpp>
#include <precise_algorithms_test.hpp>
#include <stochastic_algorithms.hpp>

int
main(int argc, char const* argv[])
{
 
  // TSP::TEST::precise_algorithms_tester test;
  // test.run();
  const auto &m = TSP::loader::load("../dane/TSP/TSP/data42.txt");
  // m.show();
  
  using TSP::STOCHASTICS::START_PATH_TYPE;
  using TSP::STOCHASTICS::COOLING_METHOD;
  using TSP::STOCHASTICS::ADJ_ALGORITHM;

  TSP::STOCHASTICS::simmulated_annealing<START_PATH_TYPE::NATURAL, 
  										 COOLING_METHOD::LOGARITHM, 
  										 ADJ_ALGORITHM::SWAP> a (m);

  return 0;
}