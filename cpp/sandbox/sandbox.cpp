#include "lib/utils/time.cpp" // ::utils::time_
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf, puts
#include <time.h>             // time_t

int main() {
  // time_t now = 1660381123;
  const long int now = 1660381123;

  puts(::utils::time_::date_string(now, "%H:%M %Z", "America/Chicago").c_str());
}
