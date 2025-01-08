#ifndef OANDA__CLI_tao_bot
#define OANDA__CLI_tao_bot

#include "oanda/tao_bot/tao_bot.cpp" // Oanda::TaoBot
#include "cli.h"                     // Oanda::Cli
#include "lib/formatted.cpp"         // Formatted
#include <stdexcept>                 // std::invalid_argument
#include <string>                    // std::string

void Oanda::Cli::tao_bot() {
  if (this->upcased_args.empty()) {
    const std::string message = Formatted::error_message(
        "Please provide at least one symbol to trade.");

    throw std::invalid_argument(message);
  }

  Oanda::TaoBot tao_bot(this->upcased_args.front(), this->flags);
  tao_bot.run();
}

#endif
