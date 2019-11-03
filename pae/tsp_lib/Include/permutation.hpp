#pragma once
#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <time.h>
#include <stdio.h>

namespace TSP {
template<typename T>
void
make_rand_permutation(T* begin, T* end)
{
  T permutation_scope = (end - begin) + 1;
  srand(time(0));

  for (auto b = begin; b != end; b++) {
    std::swap(*b, *(b + rand() % permutation_scope) );
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