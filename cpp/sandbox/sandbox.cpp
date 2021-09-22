#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include <valarray>

int main() {
  std::valarray<double> vals = {-1.00, -2.2, -3.3};
  printf("%f\n", vals.min());
}
