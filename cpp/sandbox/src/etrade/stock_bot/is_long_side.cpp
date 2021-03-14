#if !defined ETRADE__STOCK_BOT_is_long_side
#define ETRADE__STOCK_BOT_is_long_side

/*
 * order_action_t
 * order_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::is_long_side(const order_t &order) {
  return order.action == order_action_t::BUY ||
         order.action == order_action_t::SELL;
}

#endif
