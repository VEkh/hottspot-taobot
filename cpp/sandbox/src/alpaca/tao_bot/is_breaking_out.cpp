#ifndef ALPACA__TAO_BOT_is_breaking_out
#define ALPACA__TAO_BOT_is_breaking_out

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <algorithm>         // std::max, std::min
#include <ctime>             // std::time
#include <math.h>            // INFINITY
#include <vector>            // std::vector

bool Alpaca::TaoBot::is_breaking_out() {
  const double current_price_ = current_price();
  const std::time_t now = std::time(nullptr);
  double max_quote = -INFINITY;
  double min_quote = INFINITY;
  std::vector<quote_t>::reverse_iterator quote_it;

  for (quote_it = this->quotes.rbegin(); quote_it != this->quotes.rend();
       quote_it++) {
    if (now - (quote_it->timestamp / 1000) > this->CONSOLIDATION_TIME_SECONDS) {
      break;
    }

    max_quote = std::max(max_quote, quote_it->price);
    min_quote = std::min(min_quote, quote_it->price);
  }

  if (max_quote == min_quote) {
    return false;
  }

  return current_price_ >= max_quote || current_price_ <= min_quote;
}

#endif
