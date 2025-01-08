#ifndef DB__CLI_execute
#define DB__CLI_execute

#include "build_candles.cpp"            // build_candles
#include "cli.h"                        // DB::Cli, handle_unknown_command
#include "import_historical_quotes.cpp" // import_historical_quotes
#include "log_snapshots.cpp"            // log_snapshots
#include "net_return.cpp"               // net_return

void DB::Cli::execute() {
  if (this->command == "build_candles") {
    build_candles();

    return;
  }

  if (this->command == "import_historical_quotes") {
    import_historical_quotes();

    return;
  }

  if (this->command == "log_snapshots") {
    log_snapshots();

    return;
  }

  if (this->command == "net_return") {
    net_return();

    return;
  }

  handle_unknown_command();
}

#endif
