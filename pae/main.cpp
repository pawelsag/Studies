#include <internals.hpp>
#include <path_manager.hpp>
#include <precise_algorithms.hpp>
#include <precise_algorithms_test.hpp>
int
main(int argc, char const* argv[])
{
  TSP::loader obj;
  auto m = obj.load_store("../dane/SMALL/data11.txt");
  m.show();


  fmt::print("Gnerating natural series...\n");
  auto series = TSP::path_manager::generate_natural_series(m.n);
  TSP::path_manager::show(series);
  auto cost = TSP::path_manager::calculate_cost(series, m);
  fmt::print("COST : {}\n", cost);

  fmt::print("Gnerating random series...\n");
  series = TSP::path_manager::generate_rand_series(m.n);
  TSP::path_manager::show(series);
  cost = TSP::path_manager::calculate_cost(series, m);
  fmt::print("COST : {}\n", cost);


  fmt::print("Gnerating defined series...\n");
  series = {1,4,2,3,6,7,9,5,8,0};
  TSP::path_manager::show(series);
  cost = TSP::path_manager::calculate_cost(series, m);
  fmt::print("COST : {}\n", cost);

  TSP::TEST::precise_algorithms_tester test;
  test.run();
  
  return 0;
}