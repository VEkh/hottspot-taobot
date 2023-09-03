#ifndef OANDA__TAO_BOT
#define OANDA__TAO_BOT

#include "tao_bot.h"      // Oanda::TaoBot
#include "initialize.cpp" // initialize
#include "run.cpp"
#include <map>    // std::map
#include <string> // std::string

Oanda::TaoBot::TaoBot(const std::string symbol_,
                      std::map<std::string, std::string> &flags_) {
  initialize(symbol_, flags_);
}

#endif
