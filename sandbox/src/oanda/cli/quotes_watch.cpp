#ifndef OANDA__CLI_quotes_watch
#define OANDA__CLI_quotes_watch

#include "cli.h"                 // Oanda::Cli
#include "lib/pg/pg.cpp"         // Pg
#include "oanda/quote/quote.cpp" // Oanda::Quote
#include <string>                // std::string

void Oanda::Cli::quotes_watch() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to watch.");

    throw std::invalid_argument(message);
  }

  Pg pg(this->flags);
  pg.connect();

  Oanda::Quote watcher(pg, this->flags);
  watcher.watch(this->upcased_args);

  pg.disconnect();
}

#endif
