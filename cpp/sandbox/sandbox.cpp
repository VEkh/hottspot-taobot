#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include "lib/utils/float.cpp"

int main() {
  const double d = 1.238919273973;

  std::cout << ::utils::float_::round_to(d, 5) << std::endl;
}
