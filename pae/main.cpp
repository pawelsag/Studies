#include <internals.hpp>
#include <path_manager.hpp>
#include <stochastic_algorithms_test.hpp>
#include <tabu_search.hpp>
#include <simulated_annealing.hpp>

using TSP::STOCHASTICS::START_PATH_TYPE;
using TSP::STOCHASTICS::COOLING_METHOD;
using TSP::STOCHASTICS::ADJ_ALGORITHM;

int
main(int argc, char const* argv[])
{

  // TSP::TEST::stochastic_algorithms_tester test;
  // test.run();
  const auto &m = TSP::loader::load("../dane/TSP/TSP/data58.txt");
  // m.show();
  TSP::STOCHASTICS::tabu_search<START_PATH_TYPE::APROX,
                                ADJ_ALGORITHM::SWAP > a(m);
  a.show_results();

  return 0;
}