#ifndef ALPACA__TAO_BOT_is_breaking_out
#define ALPACA__TAO_BOT_is_breaking_out

#include "current_price.cpp" // current_price
#include "tao_bot.h"         // Alpaca::TaoBot, quote_t
#include <algorithm>         // std::max, std::min
#include <map>               // std::map
#include <math.h>            // INFINITY

bool Alpaca::TaoBot::is_breaking_out() {
  const double current_price_ = current_price();
  double max_resistance = -INFINITY;
  double min_support = INFINITY;
  std::map<std::string, quote_t>::iterator it;

  for (it = this->momentum_reversals["resistance"].begin();
       it != this->momentum_reversals["resistance"].end(); it++) {
    max_resistance = std::max(max_resistance, it->second.price);
  }

  for (it = this->momentum_reversals["support"].begin();
       it != this->momentum_reversals["support"].end(); it++) {
    min_support = std::min(min_support, it->second.price);
  }

  return (max_resistance != -INFINITY && current_price_ > max_resistance) ||
         (min_support != INFINITY && current_price_ < min_support);
}

#endif
