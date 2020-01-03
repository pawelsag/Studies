#include <internals.hpp>
#include <path_manager.hpp>
// #include <stochastic_algorithms_test.hpp>
// #include <precise_algorithms_test.hpp>
#include <genetic_algorithms_test.hpp>
#include <tabu_search.hpp>
#include <simulated_annealing.hpp>
#include <genetic_algorithm.hpp>
#include <ant_colony.hpp>

using TSP::GENETIC::SELECTION_METHOD;
using TSP::GENETIC::CROSS_METHOD;
using TSP::GENETIC::MUTATION_METHOD;
using TSP::GENETIC::ANT_COLONY_ALG;

int
main(int argc, char const* argv[])
{


  // TSP::TEST::genetic_algorithms_tester test;
  // test.run();
 const auto &m = TSP::loader::load("../dane/TSP/TSP/data17.txt");

  // m.show();
  // TSP::STOCHASTICS::tabu_search<START_PATH_TYPE::RANDOM,
  //                               ADJ_ALGORITHM::INVERT> a(m);

  // a.show_results();


  // TSP::STOCHASTICS::simmulated_annealing<START_PATH_TYPE::APROX,
		// 							                       COOLING_METHOD::LINEAR,
  //                               	       ADJ_ALGORITHM::INVERT> ts(m);
  // ts.show_results();
  // for(int i =0 ; i< 10; i++){
  // TSP::GENETIC::genetic_algorithm<SELECTION_METHOD::RANK,
  //                                 CROSS_METHOD::OX,
  //                                 MUTATION_METHOD::INSERTION> ga(m);
  // ga.show_results();
  // }

    TSP::GENETIC::ant_colony<ANT_COLONY_ALG::QAS> ac(m);
    ac.show_results();
  return 0;
}