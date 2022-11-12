#ifndef OANDA__TAO_BOT_get_quote_price_range
#define OANDA__TAO_BOT_get_quote_price_range

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Oanda::TaoBot, quote_t
#include <algorithm>         // std::max, std::min
#include <ctime>             // std::time
#include <math.h>            // INFINITY
#include <utility>           // std::pair
#include <vector>            // std::vector

std::pair<double, double> Oanda::TaoBot::get_quote_price_range() {
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

  return {max_quote, min_quote};
}

#endif