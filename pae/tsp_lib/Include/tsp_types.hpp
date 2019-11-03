#pragma once

#include <cstdint>
#include <vector>
namespace TSP {
using tsp64_t = int64_t;
using index_t = uint32_t;
using series_t = std::vector<index_t>;
struct point
{
  tsp64_t p1, p2;
};

using path_t = std::vector<point>;

}