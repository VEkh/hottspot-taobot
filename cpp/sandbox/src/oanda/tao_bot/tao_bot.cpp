#ifndef OANDA__TAO_BOT
#define OANDA__TAO_BOT

#include "tao_bot.h"      // Oanda::TaoBot
#include "initialize.cpp" // initialize
#include "run.cpp"

Oanda::TaoBot::TaoBot(char *symbol_,
                      std::map<std::string, std::string> &flags) {
  initialize(symbol_, flags);
}

#endif
