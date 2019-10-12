#pragma once
#include <cstdlib>
#include <time.h>
#include <cstdint>
#include <tsp_types.hpp>
#include <algorithm>
#include <fmt/format.h>
namespace TSP{
    template<typename T>
    void make_permutation(std::vector<T>& vec, uint32_t permutation_scope)
    {
      srand(time(0));
      for (auto beg = vec.begin(); beg != vec.end(); beg++) {
        std::iter_swap(beg, beg + rand() % permutation_scope );
        fmt::print("{} ",*beg);
        permutation_scope--;
      }
      fmt::print("\n");
    }

    series_t generate_series(uint32_t n);
};