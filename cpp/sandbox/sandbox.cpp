#include "lib/utils/float.cpp" // ::utils::float_
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf, puts

int main() {
  const double variance_multiplier =
      ::utils::float_::sigmoid(60.0, 20.0, 0.5, -5.0, 1.0);

  printf("y: %.2f\n", variance_multiplier);
}
