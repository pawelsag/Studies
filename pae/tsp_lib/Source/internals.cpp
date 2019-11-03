#include <fstream>
#include <internals.hpp>
#include <filesystem>

namespace fs = std::filesystem;

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
  auto pos = m.source.find('.');
  m.source = m.source.substr(0, pos);
  fs >> m.n;
  tsp64_t v;

  while (fs >> v)
    m.data.push_back(v);

  return m;
}

tsp_results_t
loader::load_results(const char* file)
{
  tsp_results_t r;
  std::fstream fs(file, std::fstream::in | std::fstream::out);
  
  if (!fs.is_open()) {
    fmt::print("Can't open file !\n");
    return r;
  }

  std::string key, trash;
  tsp64_t value;
  while( !fs.eof() ){
    fs >> trash;
    fs >> key;
    auto pos = key.find(':');
    key = key.substr(0, pos);
    fs >> value;
    r[key] = value;
  }
  return r;
}

directory_info_t
loader::load_directory_files(const char* dir_path)
{
  directory_info_t info; 
  for(auto& p: fs::directory_iterator(dir_path))
      info.emplace_back(p.path());
  return info;
}

std::string loader::filter_out_results(directory_info_t& d)
{
  for(auto it = d.begin() ;it != d.end(); it++)
  {
    if(it->find("opt") != -1 || it->find("best") != -1){
      auto f_result_path = *it; 
      d.erase(it);
      return f_result_path;
    }
  }
  return "";
}

};