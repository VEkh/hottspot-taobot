#include "deps/nlohmann/json.hpp"
#include <fstream>  // std::ifstream, std::ios
#include <iostream> // std::cout
#include <string>   // stoi

using json = nlohmann::json;

int main() {
  json j;

  std::string k = "foo";
  std::string v = "bar";

  j[k] = v;

  std::cout << j << std::endl;
}
