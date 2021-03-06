#pragma once
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <time.h>
#include <stdio.h>
#include <random>

namespace TSP {

extern thread_local std::mt19937 gen;
 
template<typename T>
T random(T min, T max) {
    using dist = std::conditional_t<
        std::is_integral<T>::value,
        std::uniform_int_distribution<T>,
        std::uniform_real_distribution<T>
    >;
    return dist{min, max}(gen);
}


template<typename T>
void
make_rand_permutation(T* begin, T* end)
{
  T permutation_scope = std::distance(begin, end);
  for (auto b = begin; b != end; b++) {
    std::swap(*b, *(b + random(0u,permutation_scope)) );
    permutation_scope--;
  }
}

template<typename T>
void
reverse(T* begin, T* end)
{
  while (begin < end) {
    std::swap(*begin, *end);
    ++begin;
    --end;
  }
}
// algorithm assumes that initial set of numbers
// passed to functions is sorted in ascending order
template<typename T>
bool
next_permutation(T* begin, T* end)
{
  T *i, *j;
  if (begin + 1 >= end)
    return false;

  i = end;
  while (true) {
    j = i;
    i--;

    if (*i < *j) {
      T* k = end;
      while (*i > *k)
        k--;
      std::swap(*i, *k);
      TSP::reverse(j, end);
      return true;
    }

    if (i == begin) {
      TSP::reverse(begin, end);
      return false;
    }
  }
}

};