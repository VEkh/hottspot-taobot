#include <iostream>
#include <vector>

int main() {
  std::vector<int> n = {1, 4, 9, 16, 25};
  std::vector<int>::iterator it;

  for (it = n.begin(); it != n.end(); it++) {
    it + 1;
    std::cout << "i + 1: " << *(it + 1) << std::endl;
    std::cout << "i: " << *it << std::endl;
  }
}
