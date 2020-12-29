#if !defined ETRADE__STRADDLE_watch_buy_positions
#define ETRADE__STRADDLE_watch_buy_positions

// #include "fetch_order_status.cpp" // fetch_order_status
#include "straddle.h" // ETrade::Straddle, buy_open_order, order_status_t

void ETrade::Straddle::watch_buy_positions() {
  if (buy_open_order.id &&
      buy_open_order.status == order_status_t::ORDER_OPEN) {
    // const char *status = fetch_order_status(buy_open_order);
    return;
  }
}

#endif
