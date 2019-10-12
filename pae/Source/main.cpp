#include <internals.hpp>
#include <misc.hpp>

int
main(int argc, char const* argv[])
{
  TSP::loader obj;
  auto m = obj.load_store("../dane/SMALL/data10.txt");
  m.show();

  auto path = TSP::generate_rand_path(m.n);
  auto cost = TSP::calculate_cost(path, m);

  fmt::print("COST : {}", cost);

  return 0;
}