#ifndef ALPACA__TAO_BOT_is_next_position_long
#define ALPACA__TAO_BOT_is_next_position_long

#include "current_price.cpp"         // current_price
#include "get_quote_price_range.cpp" // get_quote_price_range
#include "lib/utils/boolean.cpp"     // ::utils::boolean
#include "tao_bot.h"                 // Alpaca::TaoBot
#include <math.h>                    // INFINITY

bool Alpaca::TaoBot::is_next_position_long() {
  if (this->quotes.empty()) {
    return ::utils::boolean::flip_coin();
  }

  const double current_price_ = current_price();
  const std::pair<double, double> quote_price_range = get_quote_price_range();
  const double max_quote = quote_price_range.first;
  const double min_quote = quote_price_range.second;

  if (max_quote == min_quote) {
    return ::utils::boolean::flip_coin();
  }

  if (max_quote != -INFINITY && current_price_ >= max_quote) {
    return true;
  }

  if (min_quote != INFINITY && current_price_ <= min_quote) {
    return false;
  }

  return ::utils::boolean::flip_coin();
};

#endif
