#pragma once
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <time.h>

namespace TSP {
template<typename T>
void
make_permutation(std::vector<T>& vec, uint32_t permutation_scope)
{
  srand(time(0));
  for (auto beg = vec.begin(); beg != vec.end(); beg++) {
    std::iter_swap(beg, beg + rand() % permutation_scope);
    permutation_scope--;
  }
}

};