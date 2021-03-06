#if !defined ETRADE__STOCK_BOT_status
#define ETRADE__STOCK_BOT_status

#include "stock_bot.h" // ETrade::StockBot, status_t

ETrade::StockBot::status_t ETrade::StockBot::status() {
  if (!buy_open_order.id && !sell_short_open_order.id) {
    return status_t::PENDING;
  }

  if (((buy_close_order.status == order_status_t::ORDER_EXECUTED ||
        buy_close_order.status == order_status_t::ORDER_OPEN) &&
       sell_short_open_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_close_order.status != order_status_t::ORDER_EXECUTED) ||
      ((sell_short_close_order.status == order_status_t::ORDER_EXECUTED ||
        sell_short_close_order.status == order_status_t::ORDER_OPEN) &&
       buy_open_order.status == order_status_t::ORDER_EXECUTED &&
       (buy_close_order.status != order_status_t::ORDER_EXECUTED))) {
    return status_t::LIMBO;
  }

  bool both_won =
      (buy_close_order.status == order_status_t::ORDER_EXECUTED &&
       sell_short_close_order.status == order_status_t::ORDER_EXECUTED);

  bool buy_won =
      (buy_close_order.status == order_status_t::ORDER_EXECUTED &&
       (sell_short_open_order.status == order_status_t::ORDER_CANCELLED ||
        sell_short_open_order.status == order_status_t::ORDER_PENDING));

  bool sell_short_won =
      (sell_short_close_order.status == order_status_t::ORDER_EXECUTED &&
       (buy_open_order.status == order_status_t::ORDER_CANCELLED ||
        buy_open_order.status == order_status_t::ORDER_PENDING));

  bool cancelled =
      ((buy_open_order.status == order_status_t::ORDER_CANCELLED ||
        buy_open_order.status == order_status_t::ORDER_PENDING ||
        buy_close_order.status == order_status_t::ORDER_CANCELLED) &&
       (sell_short_open_order.status == order_status_t::ORDER_CANCELLED ||
        sell_short_open_order.status == order_status_t::ORDER_PENDING ||
        sell_short_close_order.status == order_status_t::ORDER_CANCELLED));

  if (both_won || buy_won || sell_short_won || cancelled) {
    return status_t::CLOSED;
  }

  return status_t::OPEN;
}

#endif
