#ifndef CLI_run
#define CLI_run

#include "cli.h"           // Cli
#include "initialize.cpp"  // initialize
#include "print_usage.cpp" // print_usage

void Cli::run() {
  if (this->argc < 2) {
    print_usage();
    exit(1);
  }

  initialize();
  execute();
}

#endif
