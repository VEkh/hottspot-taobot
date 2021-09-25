#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf

#include <string>

int main() {
  std::string num = "1.17206";

  printf("%.5f\n", atof(num.c_str()));
}
