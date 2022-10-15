#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/float.cpp" // ::utils::float_
#include "lib/utils/io.cpp"    // ::utils::io
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf, puts

int main() {
  const double one_sec_variance = 0.0377094901321994;
  const double trailing_stop_coefficient = ::utils::float_::sigmoid(
      10, 1, 1 * one_sec_variance, 10, 10 * one_sec_variance);

  printf("Coefficient: %.5f\n", trailing_stop_coefficient);
}
