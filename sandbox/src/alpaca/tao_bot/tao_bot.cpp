#ifndef ALPACA__TAO_BOT
#define ALPACA__TAO_BOT

#include "tao_bot.h"      // Alpaca::TaoBot, init_order_action
#include "initialize.cpp" // initialize
#include "run.cpp"        // run
#include <string>         // std::string

Alpaca::TaoBot::TaoBot(std::string symbol_,
                       std::map<std::string, std::string> &flags_) {
  initialize(symbol_, flags_);
}

#endif
