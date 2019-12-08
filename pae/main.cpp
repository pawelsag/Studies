#include <internals.hpp>
#include <path_manager.hpp>
#include <stochastic_algorithms_test.hpp>
#include <precise_algorithms_test.hpp>
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
  const auto &m = TSP::loader::load("../dane/SMALL/data18.txt");
  // m.show();
  TSP::STOCHASTICS::tabu_search<START_PATH_TYPE::APROX,
                                ADJ_ALGORITHM::INSERT> a(m);

  a.show_results();

  // TSP::STOCHASTICS::simmulated_annealing<START_PATH_TYPE::APROX,
		// 							  COOLING_METHOD::LINEAR,
  //                               	  ADJ_ALGORITHM::INVERT> ts(m);
  // ts.show_results();
  return 0;
}