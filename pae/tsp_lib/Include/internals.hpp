#pragma once

#include <fmt/format.h>
#include <string>
#include <vector>
#include <tsp_types.hpp>


namespace TSP {

template<typename T, typename = typename std::is_fundamental<T>::type>
struct matrix
{
  using matrix_t = std::vector<T>;

  matrix_t data = {};
  std::string source = "";
  uint32_t n = 0;

  matrix() = default;
  ~matrix() = default;

  matrix(index_t n)
  {
    this->n = n;
    this->data.resize(this->n * this->n);
  }

  matrix(const matrix<T>& m)
  {
    this->source = m.source;
    this->n = m.n;
    this->data = m.data;
  }

  matrix& operator=(const matrix<T>& m)
  {
    this->source = m.source;
    this->n = m.n;
    this->data = m.data;
    return *this;
  }

  matrix(matrix<T>&& m)
  {
    this->source = m.source;
    this->n = m.n;
    this->data = std::move(m.data);
    m.n = 0;
  }

  matrix& operator=(matrix<T>&& m)
  {
    this->source = m.source;
    this->n = m.n;
    this->data = std::move(m.data);
    m.n = 0;
    return *this;
  }

  matrix_t & get_ineternal()
  {
    return data;
  }

  inline T get_value(index_t r, index_t c) const noexcept
  {
    return this->data[r * n + c];
  }

  inline void set_value(T val, index_t r, index_t c) noexcept
  {
    this->data[r * n + c] = val;
  }
  inline void fill(T val)
  {
    for (auto v = this->data.begin(); v !=this->data.end(); v++ ) 
      *v = val;
  }

  void show() const
  {
    index_t line_break = 1;

    fmt::print("Source : {} \n", this->source);
    fmt::print("Rows   : {} \n", this->n);
    fmt::print("Size   : {} \n", this->data.size());

    for (const auto& v : this->data) {
      line_break % this->n != 0 ? fmt::print("{} ", v) : fmt::print("{} \n", v);
      line_break++;
    }
  }
};

class loader
{
  matrix<tsp64_t> cache;

public:
  loader() = default;
  ~loader() = default;
  matrix<tsp64_t> load_store(const char*);
  inline matrix<tsp64_t> get_data() const noexcept { return this->cache; }

  static matrix<tsp64_t> load(const char*);
  static tsp_results_t load_results(const char*);
  static directory_info_t load_directory_files(const char* dir_path);
  static std::string filter_out_results(directory_info_t& d);
};

};