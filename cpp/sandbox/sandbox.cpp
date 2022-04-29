#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/float.cpp" // ::utils::float_

int main() {
  const double y = ::utils::float_::sigmoid(0.002, 0.00125, 1.0, 5, 1.5);

  printf("Value: %.5f\n", y);
}
