#ifndef ALPACA__CLI_execute
#define ALPACA__CLI_execute

#include "cancel_orders.cpp"  // cancel_orders
#include "cli.h"              // Alpaca::Cli, handle_unknown_command
#include "fetch_asset.cpp"    // fetch_asset
#include "fetch_quote.cpp"    // fetch_quote
#include "log_benchmark.cpp"  // log_benchmark
#include "quotes_stream.cpp"  // quotes_stream
#include "quotes_watch.cpp"   // quotes_watch
#include "stream_account.cpp" // stream_account
#include "tao_bot.cpp"        // tao_bot

void Alpaca::Cli::execute() {
  if (this->command == "cancel_orders") {
    cancel_orders();

    return;
  }

  if (this->command == "fetch_asset") {
    fetch_asset();

    return;
  }

  if (this->command == "fetch_quote") {
    fetch_quote();

    return;
  }

  if (this->command == "log_benchmark") {
    log_benchmark();

    return;
  }

  if (this->command == "quotes_stream") {
    quotes_stream();

    return;
  }

  if (this->command == "quotes_watch") {
    quotes_watch();

    return;
  }

  if (this->command == "stream_account") {
    stream_account();

    return;
  }

  if (this->command == "tao_bot") {
    tao_bot();

    return;
  }

  handle_unknown_command();
}

#endif
