#if !defined ETRADE__STRADDLE_status
#define ETRADE__STRADDLE_status

#include "straddle.h" // ETrade::Straddle, status_t

ETrade::Straddle::status_t ETrade::Straddle::status() {
  if (!buy_open_order.id && !sell_short_open_order.id) {
    return status_t::PENDING;
  }

  bool buy_won =
      (buy_profit_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_open_order.status == order_status_t::ORDER_CANCELLED);

  bool buy_lost_sell_short_won =
      (buy_stop_loss_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_profit_order.status == order_status_t::ORDER_EXECUTED);

  bool sell_short_won =
      (sell_short_profit_order.status == order_status_t::ORDER_EXECUTED &&
       buy_open_order.status == order_status_t::ORDER_CANCELLED);

  bool sell_short_lost_buy_won =
      (sell_short_stop_loss_order.status == order_status_t::ORDER_EXECUTED &&
       buy_profit_order.status == order_status_t::ORDER_EXECUTED);

  if (buy_won || sell_short_won || buy_lost_sell_short_won ||
      sell_short_lost_buy_won) {
    return status_t::CLOSED;
  }

  return status_t::OPEN;
}

#endif
