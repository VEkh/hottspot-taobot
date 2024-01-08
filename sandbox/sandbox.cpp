#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/float.cpp" // ::utils::float_
#include <math.h>              // pow

int main(int argc, char *argv[]) {
  const double x = (1.0 / pow(10, 2)) * 90;

  const double y = ::utils::float_::sigmoid({
      .decay_rate = -1e-2,
      .max = 20.0,
      .min = 1e-4,
      .x = (1.0 / (2 * 0.9)) * 10 * 60,
      .x_shift = 3 * 60,
  });

  printf("%f\n", y);
}
