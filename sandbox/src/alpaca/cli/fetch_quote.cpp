#ifndef ALPACA__CLI_fetch_quote
#define ALPACA__CLI_fetch_quote

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "cli.h"                    // Alpaca::Cli
#include "lib/formatted.cpp"        // Formatted
#include <iostream>                 // std::cout, std::endl
#include <stdexcept>                // std::invalid_argument
#include <stdio.h>                  // printf
#include <string>                   // std::string

void Alpaca::Cli::fetch_quote() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to fetch.");

    throw std::invalid_argument(message);
  }

  Alpaca::Client alpaca_client(this->flags);

  const std::string quote =
      alpaca_client.fetch_quote(this->upcased_args.front());

  std::cout << quote << std::endl;
}

#endif
