#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/float.cpp" // ::utils::float_
#include "lib/utils/io.cpp"    // ::utils::io
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf, puts
#include <valarray>            // std::valarray

int main() {
  const std::valarray<double> vals = {1.0, 2.5, 0.3};

  printf("Max: %.2f\n", vals.max());
}
