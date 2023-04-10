#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/utils/debug.cpp" // ::utils::debug
#include "lib/utils/io.cpp"    // ::utils::io

int main(int argc, char *argv[]) {
  std::map<std::string, std::string> flags =
      ::utils::io::extract_flags(argc, argv);

  ::utils::debug::inspect(flags);
}
