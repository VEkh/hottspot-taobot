#if !defined TD_AMERITRADE__STRADDLE_manual_run
#define TD_AMERITRADE__STRADDLE_manual_run

#include "fetch_current_quote.cpp"   // fetch_current_quote
#include "log_prices.cpp" // log_prices
#include "set_order_prices.cpp"      // set_order_prices

#include "straddle.h" // TdAmeritrade::Straddle, td_ameritrade_client

void TdAmeritrade::Straddle::manual_run() {
  td_ameritrade_client.refresh_tokens();
  fetch_current_quote();
  set_order_prices();
  log_prices();
}

#endif
