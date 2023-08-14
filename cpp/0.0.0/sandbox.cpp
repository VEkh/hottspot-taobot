#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/time.cpp" // ::utils::time_
#include <time.h>             // time

int main(int argc, char *argv[]) {
  const tm time_parts = {
      .tm_sec = 30,
      .tm_min = 21,
      .tm_hour = 17,
  };

  printf("is at least?: %i\n", (int)::utils::time_::is_before(time_parts));
}
