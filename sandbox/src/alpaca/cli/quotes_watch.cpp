#ifndef ALPACA__CLI_quotes_watch
#define ALPACA__CLI_quotes_watch

#include "alpaca/quote/quote.cpp" // Alpaca::Quote
#include "cli.h"                  // Alpaca::Cli
#include "lib/formatted.cpp"      // Formatted
#include "lib/pg/pg.cpp"          // Pg
#include <stdexcept>              // std::invalid_argument

void Alpaca::Cli::quotes_watch() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to watch.");

    throw std::invalid_argument(message);
  }

  Pg pg(this->flags);
  pg.connect();

  Alpaca::Quote watcher(pg, this->flags);
  watcher.watch(this->upcased_args);

  pg.disconnect();
}

#endif
