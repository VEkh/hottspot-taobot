#if !defined ETRADE__STOCK_BOT_manual_run
#define ETRADE__STOCK_BOT_manual_run

#include "fetch_and_set_quote.cpp" // fetch_and_set_quote
#include "log_prices.cpp"          // log_prices
#include "set_order_prices.cpp"    // set_order_prices

#include "stock_bot.h" // ETrade::StockBot, etrade_client

void ETrade::StockBot::manual_run() {
  etrade_client.refresh_token();
  fetch_and_set_quote();
  set_order_prices();
  log_prices();
}

#endif
