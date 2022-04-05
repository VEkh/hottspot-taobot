#ifndef ALPACA__TAO_BOT_hedge_symbol
#define ALPACA__TAO_BOT_hedge_symbol

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::string

std::string Alpaca::TaoBot::hedge_symbol() {
  return this->HEDGE_PAIRS[this->symbol].symbol;
}

#endif
