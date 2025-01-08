#ifndef OANDA__CLI_fetch_quote
#define OANDA__CLI_fetch_quote

#include "cli.h"                   // Oanda::Cli
#include "lib/formatted.cpp"       // Formatted
#include "oanda/client/client.cpp" // Oanda::Client
#include <iostream>                // std::cout, std::endl
#include <stdexcept>               // std::invalid_argument
#include <string>                  // std::string

void Oanda::Cli::fetch_quote() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to trade.");

    throw std::invalid_argument(message);
  }

  const std::string symbol = this->upcased_args.front();
  Oanda::Client oanda_client(this->flags);

  const std::string quote = oanda_client.fetch_quote(symbol);
  std::cout << quote << std::endl;
}

#endif
