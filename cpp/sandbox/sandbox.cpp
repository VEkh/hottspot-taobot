#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/time.cpp" // ::utils::time_
#include <time.h>             // time

int main(int argc, char *argv[]) {
  const double now = time(nullptr);

  int out = ::utils::time_::day_of_week(1680615000.000000);

  printf("%i\n", (int)out);
}
