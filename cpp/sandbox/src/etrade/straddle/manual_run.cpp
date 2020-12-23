#if !defined ETRADE__STRADDLE_manual_run
#define ETRADE__STRADDLE_manual_run

#include "log_manual_run_prices.cpp" // log_manual_run_prices
#include "set_current_quote.cpp"     // set_current_quote
#include "set_order_prices.cpp"      // set_order_prices

#include "straddle.h" // ETrade::Straddle, etrade_client

void ETrade::Straddle::manual_run() {
  etrade_client.refresh_token();
  set_current_quote();
  set_order_prices();
  log_manual_run_prices();
}

#endif
