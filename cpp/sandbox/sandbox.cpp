#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/string.cpp" // ::utils::string

int main() {
  const char *str = "jay-z";
  printf("%s\n", ::utils::string::upcase(str).c_str());
}
