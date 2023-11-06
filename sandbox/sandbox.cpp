#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/float.cpp" // ::utils::float::sigmoid

int main(int argc, char *argv[]) {
  const double val = ::utils::float_::sigmoid({
      .max = 1,
      .min = 0.1,
      .x = 0.9,
      .x_coefficient = 15.0,
      .x_shift = 0.75,
  });

  printf("%f\n", val);
}
