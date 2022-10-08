#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/io.cpp"    // ::utils::io
#include <algorithm>           // std::copy
#include <iostream>            // std::cout, std::endl
#include <map>                 // std::vector
#include <stdio.h>             // printf, puts
#include <string>              // std::string

int main() {
  std::map<std::string, int> m = {{"foo", 1}, {"bar", 2}};

  ::utils::debug::inspect(m);
}
