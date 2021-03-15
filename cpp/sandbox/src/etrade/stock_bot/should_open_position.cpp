#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

#include "set_max_buy_sell_ratio.cpp" // set_max_buy_sell_ratio
#include "stock_bot.h"                // ETrade::StockBot, quote_t

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();

  const double buy_sell_ratio =
      current_quote.simple_moving_average.buy_sell_ratio;

  const double sell_buy_ratio =
      current_quote.simple_moving_average.sell_buy_ratio;

  const double entry_threshold = 1.15;

  if (buy_sell_ratio >= entry_threshold || sell_buy_ratio >= entry_threshold) {
    this->is_long_position = buy_sell_ratio >= entry_threshold;
    set_max_buy_sell_ratio();

    return true;
  }

  return false;
}

#endif
