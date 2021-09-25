#ifndef ETRADE__TAO_BOT_set_average_tick_price_delta
#define ETRADE__TAO_BOT_set_average_tick_price_delta

/*
 * ETrade::TaoBot
 * quote_t
 */
#include "tao_bot.h"

#include <math.h> // abs
#include <vector> // std::vector

void ETrade::TaoBot::set_average_tick_price_delta() {
  const quote_t current_quote = this->quotes.back();

  if (current_quote.timestamp - this->quotes.front().timestamp <
      this->AVERAGE_TICK_PRICE_DELTA_PERIOD) {
    return;
  }

  double total = 0;
  int ticks = 0;
  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); current_quote.timestamp - it->timestamp <=
                                       this->AVERAGE_TICK_PRICE_DELTA_PERIOD &&
                                   it != this->quotes.rend();
       it++) {

    double delta = abs(it->price - (it + 1)->price);
    total += delta;
    ticks++;
  }

  this->average_tick_price_delta = total / ticks;
}

#endif
