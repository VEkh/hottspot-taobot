#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/float.cpp" // ::utils::float_
#include <algorithm>           // std::min
#include <valarray>            // std::string

int main() {
  const double a = 0.5, b = 1.0;
  const double avg = (a + b) / 2.0;

  printf("a ratio: %.5f; b ratio: %.5f\n", a / avg, b / avg);
  printf("ratio: %.5f\n", (a / avg) / (b / avg));
}
