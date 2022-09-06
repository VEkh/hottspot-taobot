#ifndef OANDA__TAO_BOT_set_price_movement
#define OANDA__TAO_BOT_set_price_movement

#include "current_spread.cpp" // current_spread
#include "spread_limit.cpp"   // spread_limit
#include "tao_bot.h"          // Oanda::TaoBot, quote_t
#include <math.h>             // abs
#include <vector>             // std::vector

void Oanda::TaoBot::set_price_movement() {
  if (!this->quotes.size()) {
    return;
  }

  if (current_spread() > spread_limit()) {
    return;
  }

  const quote_t current_quote = this->quotes.back();

  if (current_quote.timestamp - this->quotes.front().timestamp <
      this->AVG_ONE_SEC_VARIANCE_TIMEFRAME) {
    return;
  }

  double total = 0;
  int ticks = 0;
  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes.rbegin(); current_quote.timestamp - it->timestamp <=
                                       this->AVG_ONE_SEC_VARIANCE_TIMEFRAME &&
                                   it != this->quotes.rend();
       it++) {

    const double time_delta = (it->timestamp - (it + 1)->timestamp) / 1000.0;
    const double delta = (it->price - (it + 1)->price) / time_delta;

    total += abs(delta);
    ticks++;
  }

  const double average = total / ticks;

  if (average > 1.0e6) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    const quote_t penultimate_quote = this->quotes.at(this->quotes.size() - 2);
    printf("Last Quote: %.2f • Last Price Delta: %.2f\n", current_quote.price,
           (current_quote.price - penultimate_quote.price));
    std::cout << fmt.reset << std::endl;

    return;
  }

  const double cumulative_max_sample_size = this->PRICE_MOVEMENT_SAMPLE_SIZE;
  const double short_term_max_sample_size = 30;

  const double old_short_term_average =
      this->price_movement.short_term_three_minute_one_second_variance.average;

  const long int old_short_term_count =
      this->price_movement.short_term_three_minute_one_second_variance.count;

  const double short_term_average =
      ((old_short_term_average * old_short_term_count) + average) /
      (old_short_term_count + 1);

  const double old_cumulative_average =
      this->price_movement.three_minute_one_second_variance.average;

  const long int old_cumulative_count =
      this->price_movement.three_minute_one_second_variance.count;

  const double cumulative_average =
      ((old_cumulative_average * old_cumulative_count) + average) /
      (old_cumulative_count + 1);

  this->price_movement.three_minute_one_second_variance.average =
      cumulative_average;

  this->price_movement.three_minute_one_second_variance.count =
      std::min(cumulative_max_sample_size, (double)(old_cumulative_count + 1));

  this->price_movement.short_term_three_minute_one_second_variance.average =
      short_term_average;

  this->price_movement.short_term_three_minute_one_second_variance.count =
      std::min(short_term_max_sample_size, (double)(old_short_term_count + 1));
}

#endif
