#ifndef ALPACA__TAO_BOT_is_hedging
#define ALPACA__TAO_BOT_is_hedging

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::stoi

bool Alpaca::TaoBot::is_hedging() {
  return this->flags["hedge"].empty() ? false
                                      : (bool)std::stoi(this->flags["hedge"]);
}

#endif
