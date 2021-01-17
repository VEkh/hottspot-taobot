#include "deps.cpp"
#include <iostream>

int main() {
  json array = R"([1,2,3])"_json;

  std::cout << *(array.end() - 2) << std::endl;
}
