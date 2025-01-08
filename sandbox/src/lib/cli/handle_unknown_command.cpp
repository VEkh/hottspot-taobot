#ifndef CLI_handle_unknown_command
#define CLI_handle_unknown_command

#include "cli.h"           // Cli, fmt
#include "print_usage.cpp" // print_usage
#include <iostream>        // std::cout, std::endl
#include <stdio.h>         // printf

void Cli::handle_unknown_command() {
  std::cout << fmt.bold << fmt.red;
  printf("Unknown command <%s>. Please refer to usage👇🏾\n\n",
         this->command.c_str());
  std::cout << fmt.reset;

  print_usage();
  exit(127);
}

#endif
