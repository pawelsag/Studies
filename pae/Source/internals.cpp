#include <fstream>
#include <internals.hpp>
namespace TSP {

matrix<tsp64_t>
loader::load_store(const char* file)
{
  this->cache = loader::load(file);
  return this->cache;
}

matrix<tsp64_t>
loader::load(const char* file)
{
  std::fstream fs(file, std::fstream::in | std::fstream::out);
  matrix<tsp64_t> m;

  if (!fs.is_open()) {
    fmt::print("Can't open file !\n");
    return m;
  }

  fs >> m.source;
  fs >> m.n;
  tsp64_t v;

  while (fs >> v)
    m.data.push_back(v);

  return m;
}
};