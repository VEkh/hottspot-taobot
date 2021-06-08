#ifndef ETRADE__STOCK_BOT_run
#define ETRADE__STOCK_BOT_run

#include "log_start_message.cpp" // log_start_message
#include "stock_bot.h"           // ETrade::StockBot, fmt, quantity, symbol
#include "watch.cpp"             // watch

void ETrade::StockBot::run() {
  log_start_message();
  watch();
}

#endif
