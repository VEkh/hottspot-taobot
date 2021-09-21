#ifndef ETRADE__TAO_BOT
#define ETRADE__TAO_BOT

#include "tao_bot.h"      // ETrade::TaoBot, init_order_action
#include "initialize.cpp" // initialize
#include "run.cpp"        // run

ETrade::TaoBot::TaoBot(char *symbol_, int quantity_,
                       std::map<std::string, std::string> &flags) {
  initialize(symbol_, quantity_, flags);
}

#endif
