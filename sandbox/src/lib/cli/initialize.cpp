#ifndef CLI_initialize
#define CLI_initialize

#include "cli.h"                // Cli
#include "lib/utils/io.cpp"     // ::utils::io
#include "lib/utils/string.cpp" // ::utils::string

void Cli::initialize() {
  this->command = this->argv[1];

  this->args = ::utils::io::extract_args(this->argc, this->argv);
  this->args.pop_front(); // Remove command arg

  this->upcased_args = ::utils::io::extract_args(this->argc, this->argv,
                                                 ::utils::string::upcase);

  this->upcased_args.pop_front(); // Remove command arg

  this->flags = ::utils::io::extract_flags(this->argc, this->argv);
}

#endif
