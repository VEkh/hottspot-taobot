#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string
#include <valarray> // std::valarray
#include <vector>   // std::vector

int main(int argc, char *argv[]) {
  std::vector<int> n = {1, 2};

  n.push_back(4);

  std::valarray<int> v(n.data(), n.size());

  printf("%i\n", v.sum());
}
