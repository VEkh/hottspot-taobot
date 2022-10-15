#ifndef OANDA__TAO_BOT_is_next_position_long
#define OANDA__TAO_BOT_is_next_position_long

#include "current_price.cpp"     // current_price
#include "lib/utils/boolean.cpp" // ::utils::boolean
#include "tao_bot.h"             // Oanda::TaoBot, fmt, quote_t
#include <ctime>                 // std::time
#include <math.h>                // INFINITY, abs

bool Oanda::TaoBot::is_next_position_long() {
  if (this->quotes.empty()) {
    return ::utils::boolean::flip_coin();
  }

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
