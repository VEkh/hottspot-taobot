#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp" // ::utils::time_
#include <string>

int main() {
  std::string num = "-1";

  printf("Num: %i\n", -std::stoi(num));
}
