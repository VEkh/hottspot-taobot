#include "deps.cpp" // json
#include <iostream>

int main() {
  json j = {
      {"id", 1},
      {"foo", "bar"},
  };

  if (0.0) {
    std::cout << j.dump() << std::endl;
  }
}
