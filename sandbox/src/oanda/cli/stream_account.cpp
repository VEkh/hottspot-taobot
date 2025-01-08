#ifndef OANDA__CLI_stream_account
#define OANDA__CLI_stream_account

#include "cli.h"                   // Oanda::Cli
#include "oanda/client/client.cpp" // Oanda::Client

void Oanda::Cli::stream_account() {
  Oanda::Client oanda_client(this->flags);
  oanda_client.stream_account();
}

#endif
