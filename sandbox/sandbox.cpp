#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/float.cpp" // ::utils::float_

int main(int argc, char *argv[]) {
  const double capturable_profit_ratio = ::utils::float_::sigmoid({
      .decay_rate = 15.0,
      .max = 1.0,
      .min = 0.5,
      .x = 1.0 / 0.75,
      .x_shift = 0.75,
  });

  printf("%f\n", capturable_profit_ratio);
}
