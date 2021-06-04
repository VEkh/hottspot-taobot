#if !defined ETRADE__STOCK_BOT
#define ETRADE__STOCK_BOT

#include "stock_bot.h"    // ETrade::StockBot, init_order_action
#include "initialize.cpp" // initialize
#include "run.cpp"        // run

ETrade::StockBot::StockBot(char *symbol_, int quantity_) {
  initialize(symbol_, quantity_);
}

#endif
