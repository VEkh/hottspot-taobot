#include <iostream>
#include <map>    // std::map
#include <vector> // std::vector

std::map<int, std::map<const char *, double>> map_gen() {
  std::map<int, std::map<const char *, double>> out = {{1, {{"buy", 1.04}}}};

  std::cout << (out[1]["buy"]) << std::endl;

  return out;
}

int main() {
  std::map<int, std::map<const char *, double>> out = map_gen();

  std::cout << (out[1]["buy"]) << std::endl;
}
