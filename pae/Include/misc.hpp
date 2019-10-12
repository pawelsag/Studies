#pragma once

#include <tsp_types.hpp>
#include <internals.hpp>

namespace TSP{
  template<typename T>
  tsp64_t
  calculate_cost(path_t& path, matrix<T>& m)
  {
    tsp64_t cost = 0;
    for (auto [p1, p2] : path) {
      cost += m.get_value(p1, p2);
    }
    cost += m.get_value(path.front().p1, path.back().p2);
    return cost;
  }
  template<typename T,
         typename = typename std::is_same<typename std::decay<T>::type, series_t>::type>
  path_t
  create_path(T&& s)
  {
    path_t path;
    auto last_point = s[0];

    for (int i = 1; i < s.size(); i++) {
      path.push_back({last_point, s[i]});
      last_point = s[i];
    }
    return path;
  }

  path_t generate_rand_path(uint32_t city_count);
  
};