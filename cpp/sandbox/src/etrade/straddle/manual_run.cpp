#if !defined ETRADE__STRADDLE_manual_run
#define ETRADE__STRADDLE_manual_run

#include "log_prices.cpp" // log_prices
#include "fetch_and_set_quote.cpp"     // fetch_and_set_quote
#include "set_order_prices.cpp"      // set_order_prices

#include "straddle.h" // ETrade::Straddle, etrade_client

void ETrade::Straddle::manual_run() {
  etrade_client.refresh_token();
  fetch_and_set_quote();
  set_order_prices();
  log_prices();
}

#endif
