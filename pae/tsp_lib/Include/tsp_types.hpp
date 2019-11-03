#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <map>

namespace TSP {
using tsp64_t = int64_t;
using index_t = uint32_t;
using series_t = std::vector<index_t>;
using directory_info_t = std::vector<std::string>;
using tsp_results_t = std::map<std::string, tsp64_t>;

struct point
{
  tsp64_t p1, p2;
};

using path_t = std::vector<point>;

}