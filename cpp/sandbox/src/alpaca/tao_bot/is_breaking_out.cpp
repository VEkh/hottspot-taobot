#ifndef ALPACA__TAO_BOT_is_breaking_out
#define ALPACA__TAO_BOT_is_breaking_out

#include "current_price.cpp"         // current_price
#include "get_quote_price_range.cpp" // get_quote_price_range
#include "tao_bot.h"                 // Alpaca::TaoBot

bool Alpaca::TaoBot::is_breaking_out() {
  const double current_price_ = current_price();
  const std::pair<double, double> quote_price_range = get_quote_price_range();
  const double max_quote = quote_price_range.first;
  const double min_quote = quote_price_range.second;

  if (max_quote == min_quote) {
    return false;
  }

  return current_price_ >= max_quote || current_price_ <= min_quote;
}

#endif
