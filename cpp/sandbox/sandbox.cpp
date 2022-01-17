#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/time.cpp" // ::utils::time_
#include <string>

int main() {
  std::time_t now = std::time(nullptr);

  std::string str = ::utils::time_::date_string(&now);

  printf("Today's date %s\n", str.c_str());
}
