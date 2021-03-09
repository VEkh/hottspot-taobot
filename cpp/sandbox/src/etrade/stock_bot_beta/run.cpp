#if !defined ETRADE__STOCK_BOT_BETA_run
#define ETRADE__STOCK_BOT_BETA_run

#include "log_start_message.cpp" // log_start_message
#include "stock_bot_beta.h"      // ETrade::StockBotBeta, fmt, quantity, symbol
#include "watch.cpp"             // watch

void ETrade::StockBotBeta::run() {
  log_start_message();
  watch();
}

#endif
