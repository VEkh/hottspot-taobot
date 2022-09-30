#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/io.cpp"    // ::utils::io
#include "lib/utils/time.cpp"  // ::utils::time_
#include <ctime>               // std::time
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf, puts
#include <string>              // std::string

int main() {
  std::time_t now = std::time(nullptr);

  printf("%s\n",
         ::utils::time_::date_string(now, "%FT%R", "America/Chicago").c_str());
}
