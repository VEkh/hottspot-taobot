#ifndef ALPACA__CLI_stream_account
#define ALPACA__CLI_stream_account

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "cli.h"                    // Alpaca::Cli

void Alpaca::Cli::stream_account() {
  Alpaca::Client alpaca_client(this->flags);
  alpaca_client.stream_account();
}

#endif
