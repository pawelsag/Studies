#pragma once

#include <internals.hpp>
#include <tsp_types.hpp>

namespace TSP {

class path_manager
{
public:
  path_manager() = delete;
  path_manager(path_manager&) = delete;
  ~path_manager() = delete;

  static series_t generate_rand_series(uint32_t city_count);

  static series_t generate_natural_series(uint32_t n);

  static void show(series_t n);

  template<typename M,
           typename S,
           typename = typename std::is_same<typename std::decay<S>::type,
                                            series_t>::type>
  static tsp64_t calculate_cost(S&& series, matrix<M>& m)
  {
    // code should check if largset number inside series
    // isn't greater than largest vertex in matrix
    tsp64_t cost = 0;
    const auto& path = create_path(series);
    for (auto [p1, p2] : path) {
      cost += m.get_value(p1, p2);
    }
    cost += m.get_value(path.front().p1, path.back().p2);
    return cost;
  }

private:
  static path_t create_path(series_t& s);
};

};