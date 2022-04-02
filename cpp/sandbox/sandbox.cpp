#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/float.cpp" // ::utils::float_
#include <string>              //std::getline, std::string

int main() {
  const double x = 4;
  const double y = ::utils::float_::sigmoid(2, 1, x, 1, 4);

  printf("y: %.2f\n", y);
}
