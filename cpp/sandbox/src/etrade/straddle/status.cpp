#if !defined ETRADE__STRADDLE_status
#define ETRADE__STRADDLE_status

#include "straddle.h" // ETrade::Straddle, status_t

ETrade::Straddle::status_t ETrade::Straddle::status() {
  if (!buy_open_order.id && !sell_short_open_order.id) {
    return status_t::PENDING;
  }

  bool both_won =
      (buy_profit_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_profit_order.status == order_status_t::ORDER_EXECUTED);

  bool buy_won =
      (buy_profit_order.status == order_status_t::ORDER_EXECUTED &&
       (sell_short_open_order.status == order_status_t::ORDER_CANCELLED ||
        sell_short_open_order.status == order_status_t::ORDER_PENDING));

  bool buy_lost_sell_short_won =
      (buy_stop_loss_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_profit_order.status == order_status_t::ORDER_EXECUTED);

  bool sell_short_won =
      (sell_short_profit_order.status == order_status_t::ORDER_EXECUTED &&
       (buy_open_order.status == order_status_t::ORDER_CANCELLED ||
        buy_open_order.status == order_status_t::ORDER_PENDING));

  bool sell_short_lost_buy_won =
      (sell_short_stop_loss_order.status == order_status_t::ORDER_EXECUTED &&
       buy_profit_order.status == order_status_t::ORDER_EXECUTED);

  bool cancelled =
      ((buy_open_order.status == order_status_t::ORDER_CANCELLED ||
        buy_open_order.status == order_status_t::ORDER_PENDING ||
        buy_profit_order.status == order_status_t::ORDER_CANCELLED ||
        buy_stop_loss_order.status == order_status_t::ORDER_CANCELLED) &&
       (sell_short_open_order.status == order_status_t::ORDER_CANCELLED ||
        sell_short_open_order.status == order_status_t::ORDER_PENDING ||
        sell_short_profit_order.status == order_status_t::ORDER_CANCELLED ||
        sell_short_stop_loss_order.status == order_status_t::ORDER_CANCELLED));

  if (both_won || buy_won || sell_short_won || buy_lost_sell_short_won ||
      sell_short_lost_buy_won || cancelled) {
    return status_t::CLOSED;
  }

  return status_t::OPEN;
}

#endif
