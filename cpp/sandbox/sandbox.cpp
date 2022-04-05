#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf, puts

#include "lib/utils/float.cpp" // ::utils::float_
#include <map>                 //std::map
#include <string>              //std::getline, std::string

int main() {
  std::map<std::string, int> m = {{"how", 4}};
  const char *key = "how";

  printf("val: %i\n", m[key]);
}
