#include "deps/nlohmann/json.hpp"
#include <fstream>  // std::ifstream, std::ios
#include <iostream> // std::cout
#include <string>   // stoi

using json = nlohmann::json;

int main() {
  json j;

  std::ifstream tokens_file("./config/td_ameritrade/tokens.json", std::ios::in);

  tokens_file >> j;

  std::cout << j << std::endl;
}
