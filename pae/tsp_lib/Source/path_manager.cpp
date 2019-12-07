#include <path_manager.hpp>
#include <utils.hpp>
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
series_t 
path_manager::generate_aprox_series(const matrix<tsp64_t> &m)
{
  series_t series;
  tsp64_t min = std::numeric_limits<tsp64_t>::max();
  auto visited = std::make_unique<bool[]>(m.n);
  std::memset(visited.get(), false,  m.n );

  // push begin vertex
  series.push_back(0);
  visited[0] = true;

  for (tsp64_t i = 0; i < m.n; i++)
  {  
    tsp64_t min_idx = 0;
    for(tsp64_t j = 0; j < m.n; j++)
    {
      if(visited[j] == true)
        continue;

      auto val = m.get_value(i,j);
      
      if(min > val && i != j ){
        min = val;
        min_idx = j;
      }
    }
    visited[min_idx] = true;
    series.push_back(min_idx);
    min = std::numeric_limits<tsp64_t>::max();
  }
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