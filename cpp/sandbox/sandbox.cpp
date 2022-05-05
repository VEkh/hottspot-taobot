#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/float.cpp" // ::utils::float_

int main() {
  // 1.0 => 0.075%; 1.5 => .1%; 2.5 => 0.2%; 3.5 => .5%
  const double y = ::utils::float_::sigmoid(0.005, 0.00075, 2.5, 1.25, 4.0);

  printf("Value: %.5f\n", y);
}
