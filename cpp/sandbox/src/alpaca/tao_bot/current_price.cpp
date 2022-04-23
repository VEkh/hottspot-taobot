#ifndef ALPACA__TAO_BOT_current_price
#define ALPACA__TAO_BOT_current_price

#include "tao_bot.h" // Alpaca::TaoBot
#include <string>    // std::string

double Alpaca::TaoBot::current_price(const std::string &symbol_) {
  return this->quotes[symbol_].back().price;
}

#endif
