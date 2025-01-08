#ifndef OANDA__CLI_execute
#define OANDA__CLI_execute

#include "cli.h"              // Oanda::Cli, handle_unknown_command
#include "fetch_quote.cpp"    // fetch_quote
#include "quotes_watch.cpp"   // quotes_watch
#include "stream_account.cpp" // stream_account
#include "tao_bot.cpp"        // tao_bot

void Oanda::Cli::execute() {
  if (this->command == "fetch_quote") {
    fetch_quote();

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
