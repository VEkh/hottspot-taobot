#if !defined ETRADE__STOCK_BOT_should_open_position
#define ETRADE__STOCK_BOT_should_open_position

#include "compute_buy_to_sell_ratio.cpp" // compute_buy_to_sell_ratio
#include "compute_sell_to_buy_ratio.cpp" // compute_sell_to_buy_ratio
#include "set_max_buy_sell_ratio.cpp"    // set_max_buy_sell_ratio
#include "stock_bot.h"                   // ETrade::StockBot, quote_t

bool ETrade::StockBot::should_open_position() {
  if (this->open_order_ptr) {
    return false;
  }

  const quote_t current_quote = this->quotes.back();

  const double buy_to_sell_ratio =
      compute_buy_to_sell_ratio(current_quote.simple_moving_average);

  const double sell_to_buy_ratio =
      compute_sell_to_buy_ratio(current_quote.simple_moving_average);

  const double entry_threshold = 1.15;

  if (buy_to_sell_ratio >= entry_threshold ||
      sell_to_buy_ratio >= entry_threshold) {
    this->is_long_position = buy_to_sell_ratio >= entry_threshold;
    set_max_buy_sell_ratio();

    return true;
  }

  return false;
}

#endif
