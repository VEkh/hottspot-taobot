#if !defined ETRADE__STOCK_BOT_should_close_position
#define ETRADE__STOCK_BOT_should_close_position

/*
 * ETrade::StockBot
 * order_status_t
 * quote_t
 */
#include "stock_bot.h"

bool ETrade::StockBot::should_close_position() {
  if (this->open_order.status != order_status_t::ORDER_EXECUTED) {
    return false;
  }

  if (this->close_order.status != order_status_t::ORDER_PENDING) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();

  const double buy_sell_ratio =
      current_quote.simple_moving_average.buy_sell_ratio;

  const double sell_buy_ratio =
      current_quote.simple_moving_average.sell_buy_ratio;

  const double loss_exit_ratio = 1.0;
  const double profit_exit_ratio = this->max_buy_sell_ratio - 0.1;

  if (this->is_long_position) {
    if (this->open_order.profit > 0) {
      return buy_sell_ratio < profit_exit_ratio;
    } else {
      return sell_buy_ratio >= loss_exit_ratio;
    }
  } else {
    if (this->open_order.profit > 0) {
      return sell_buy_ratio < profit_exit_ratio;
    } else {
      return buy_sell_ratio >= loss_exit_ratio;
    }
  }

  return false;
}

#endif
