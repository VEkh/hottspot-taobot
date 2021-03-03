#include "deps.cpp"
#include <iostream>

int main() {
  json j = R"([1, 2, 3])"_json;

  json::reverse_iterator it = j.rbegin();

  int i;

  for (i = 0; i < j.size(); i++) {
    std::cout << *it << std::endl;
    it++;
  }

  std::cout << j << std::endl;
  std::cout << i << std::endl;
}
