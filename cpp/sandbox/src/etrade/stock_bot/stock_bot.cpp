#ifndef ETRADE__STOCK_BOT
#define ETRADE__STOCK_BOT

#include "stock_bot.h"    // ETrade::StockBot, init_order_action
#include "initialize.cpp" // initialize
#include "run.cpp"        // run

ETrade::StockBot::StockBot(char *symbol_, int quantity_,
                           std::map<std::string, std::string> &flags) {
  initialize(symbol_, quantity_, flags);
}

#endif
