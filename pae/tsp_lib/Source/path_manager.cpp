#include <path_manager.hpp>
#include <permutation.hpp>
#include <fmt/format.h>

namespace TSP {
series_t
path_manager::generate_rand_series(uint32_t city_count)
{
  auto series = generate_natural_series(city_count);
  make_rand_permutation(&series.front(), &series.back());

  return series;
}

series_t
path_manager::generate_natural_series(uint32_t n)
{
  series_t series;
  for (uint32_t i = 0; i < n; i++)
    series.push_back(i);
  return series;
}

path_t
path_manager::create_path(series_t &s)
{
  path_t path;
  auto last_point = s[0];

  for (uint i = 1; i < s.size(); i++) {
    path.push_back({ last_point, s[i] });
    last_point = s[i];
  }
  return path;
}

void
path_manager::show(series_t s){
  for(const auto & v : s)
    fmt::print("{} ", v);
  fmt::print("\n");
}

};