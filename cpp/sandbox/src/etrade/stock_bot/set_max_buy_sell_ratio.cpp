#if !defined ETRADE__STOCK_BOT_set_max_buy_sell_ratio
#define ETRADE__STOCK_BOT_set_max_buy_sell_ratio

#include "compute_buy_to_sell_ratio.cpp" // compute_buy_to_sell_ratio
#include "compute_sell_to_buy_ratio.cpp" // compute_sell_to_buy_ratio
#include "stock_bot.h"                   // ETrade::StockBot, quote_t
#include <algorithm>                     // std::max

void ETrade::StockBot::set_max_buy_sell_ratio() {
  if (!this->open_order_ptr) {
    return;
  }

  const quote_t current_quote = this->quotes.back();

  const double buy_to_sell_ratio =
      compute_buy_to_sell_ratio(current_quote.simple_moving_average);

  const double sell_to_buy_ratio =
      compute_sell_to_buy_ratio(current_quote.simple_moving_average);

  const double profit_ratio =
      this->is_long_position ? buy_to_sell_ratio : sell_to_buy_ratio;

  this->max_buy_sell_ratio = std::max(this->max_buy_sell_ratio, profit_ratio);
}

#endif
