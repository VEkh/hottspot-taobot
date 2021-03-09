#if !defined ETRADE__STOCK_BOT_BETA
#define ETRADE__STOCK_BOT_BETA

#include "stock_bot_beta.h" // ETrade::StockBotBeta, init_order_action
#include "initialize.cpp"   // initialize
#include "run.cpp"          // run

ETrade::StockBotBeta::StockBotBeta(char *symbol_, int quantity_) {
  initialize(symbol_, quantity_);
}

#endif
