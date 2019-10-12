#include <misc.hpp>


namespace TSP {

series_t
generate_series(uint32_t n)
{
  std::vector<uint32_t> series;
  for (uint32_t i = 0; i < n; i++)
    series.push_back(i);
  return series;
}

}