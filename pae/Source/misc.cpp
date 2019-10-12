#include <permutation.hpp>
#include <misc.hpp>

namespace TSP {
path_t
generate_rand_path(uint32_t city_count)
{
  auto series = generate_series(city_count);
  make_permutation(series, city_count);

  return create_path(series);
}

};