#ifndef ALPACA__TAO_BOT
#define ALPACA__TAO_BOT

#include "tao_bot.h"      // Alpaca::TaoBot, init_order_action
#include "initialize.cpp" // initialize
#include "run.cpp"        // run

Alpaca::TaoBot::TaoBot(char *symbol_,
                       std::map<std::string, std::string> &flags_) {
  initialize(symbol_, flags_);
}

#endif
