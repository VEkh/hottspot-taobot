#if !defined ETRADE__STOCK_BOT_BETA_watch
#define ETRADE__STOCK_BOT_BETA_watch

#include "fetch_quote.cpp"  // fetch_quote
#include "log_quote.cpp"    // log_quote
#include "stock_bot_beta.h" // ETrade::StockBotBeta, POLLING_INTERVAL_SECONDS
#include <chrono>           // std::chrono
#include <thread>           // std::this_thread

void ETrade::StockBotBeta::watch() {
  while (true) {
    fetch_quote();
    log_quote();

    std::this_thread::sleep_for(
        std::chrono::milliseconds((int)(POLLING_INTERVAL_SECONDS * 1000)));
  }
}

#endif
