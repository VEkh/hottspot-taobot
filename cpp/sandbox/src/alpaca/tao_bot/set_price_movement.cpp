#ifndef ALPACA__TAO_BOT_set_price_movement
#define ALPACA__TAO_BOT_set_price_movement

#include "tao_bot.h"                // Alpaca::TaoBot, quote_t
#include "write_price_movement.cpp" // write_price_movement
#include <math.h>                   // abs
#include <vector>                   // std::vector

void Alpaca::TaoBot::set_price_movement() {
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

  const double average = total / ticks;

  const double old_cumulative_average =
      this->price_movement.three_minute_one_second_variance.average;

  const double old_cumulative_count =
      this->price_movement.three_minute_one_second_variance.count;

  const double cumulative_average =
      ((old_cumulative_average * old_cumulative_count) + average) /
      (old_cumulative_count + 1);

  this->price_movement.three_minute_one_second_variance.average =
      cumulative_average;
  this->price_movement.three_minute_one_second_variance.count++;

  write_price_movement();
}

#endif
