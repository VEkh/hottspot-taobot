#ifndef CLI_print_usage
#define CLI_print_usage

#include "cli.h"    // Cli, fmt
#include <iostream> // std::cout, std::endl
#include <map>      // std::map
#include <string>   // std::string

void Cli::print_usage() {
  std::cout << fmt.bold << fmt.cyan;
  printf("%s Client Usage", this->cli_name.c_str());
  std::cout << std::endl;

  std::map<std::string, std::string>::iterator it;

  for (it = this->commands.begin(); it != this->commands.end(); ++it) {
    std::cout << fmt.bold << fmt.yellow << it->first << fmt.reset << " | "
              << it->second << std::endl;
  }
}

#endif
