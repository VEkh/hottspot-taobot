#include "deps.cpp" // json
#include <iostream>

int main() {
  json j;

  if (j["yerr"]["foo"]) {
    std::cout << "😲" << std::endl;
  }
}
