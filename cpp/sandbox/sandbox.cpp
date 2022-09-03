#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/io.cpp"    // ::utils::io
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // printf, puts
#include <string>              // std::string
#include <vector>              // std::vector

int main() {
  std::vector<std::string> symbols = ::utils::io::tradeable_symbols("alpaca");

  ::utils::debug::inspect(symbols);

  printf("count: %i\n", (int)symbols.size());
}
