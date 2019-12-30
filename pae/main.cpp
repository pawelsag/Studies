#include <internals.hpp>
#include <path_manager.hpp>
#include <stochastic_algorithms_test.hpp>
#include <precise_algorithms_test.hpp>
#include <tabu_search.hpp>
#include <simulated_annealing.hpp>
#include <genetic_algorithm.hpp>

using TSP::GENETIC::SELECTION_METHOD;
using TSP::GENETIC::CROSS_METHOD;
using TSP::GENETIC::MUTATION_METHOD;

int
main(int argc, char const* argv[])
{

  // TSP::TEST::stochastic_algorithms_tester test;
  // test.run();
  const auto &m = TSP::loader::load("../dane/TSP/TSP/data120.txt");
  // m.show();
  // TSP::STOCHASTICS::tabu_search<START_PATH_TYPE::RANDOM,
  //                               ADJ_ALGORITHM::INVERT> a(m);

  // a.show_results();

  // TSP::STOCHASTICS::simmulated_annealing<START_PATH_TYPE::APROX,
		// 							                       COOLING_METHOD::LINEAR,
  //                               	       ADJ_ALGORITHM::INVERT> ts(m);
  // ts.show_results();

  TSP::GENETIC::genetic_algorithm<SELECTION_METHOD::RANK,
                                  CROSS_METHOD::PMX,
                                  MUTATION_METHOD::INSERTION> ga(m);
  ga.show_results();
  return 0;
}