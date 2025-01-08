#ifndef ALPACA__CLI_tao_bot
#define ALPACA__CLI_tao_bot

#include "alpaca/tao_bot/tao_bot.cpp" // Alpaca::TaoBot
#include "cli.h"                      // Alpaca::Cli
#include "lib/formatted.cpp"          // Formatted
#include <stdexcept>                  // std::invalid_argument

void Alpaca::Cli::tao_bot() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to trade.");

    throw std::invalid_argument(message);
  }

  Alpaca::TaoBot tao_bot(this->upcased_args.front(), this->flags);
  tao_bot.run();
}

#endif
