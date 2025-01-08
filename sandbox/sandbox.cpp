#include <iostream> // std::cout, std::endl
#include <regex>    // std::regex, std::regex_search, std::smatch
#include <stdio.h>  // printf
#include <string>   // std::string

#include "lib/cli/cli.cpp" // ::Cli

int main(int argc, char *argv[]) {
  ::Cli cli(argc, argv);
  cli.run();
}
