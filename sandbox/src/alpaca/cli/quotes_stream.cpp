#ifndef ALPACA__CLI_quotes_stream
#define ALPACA__CLI_quotes_stream

#include "alpaca/quote/quote.cpp" // Alpaca::Quote
#include "cli.h"                  // Alpaca::Cli
#include "lib/formatted.cpp"      // Formatted
#include "lib/pg/pg.cpp"          // Pg
#include <stdexcept>              // std::invalid_argument

void Alpaca::Cli::quotes_stream() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to stream.");

    throw std::invalid_argument(message);
  }

  Pg pg(this->flags);
  pg.connect();

  Alpaca::Quote streamer(pg, this->flags);
  streamer.stream(this->upcased_args);

  pg.disconnect();
}

#endif
