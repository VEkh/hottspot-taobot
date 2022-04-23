#ifndef ALPACA__TAO_BOT_set_price_movement
#define ALPACA__TAO_BOT_set_price_movement

#include "tao_bot.h"                // Alpaca::TaoBot, quote_t
#include "write_price_movement.cpp" // write_price_movement
#include <math.h>                   // abs, INFINITY
#include <string>                   // std::string
#include <vector>                   // std::vector

void Alpaca::TaoBot::set_price_movement(const std::string &symbol_) {
  std::vector<quote_t> quotes_ = this->quotes[symbol_];

  if (!quotes_.size()) {
    return;
  }

  const quote_t current_quote = quotes_.back();

  if (current_quote.timestamp - quotes_.front().timestamp <
      this->AVERAGE_TICK_PRICE_DELTA_PERIOD) {
    return;
  }

  double total = 0;
  int ticks = 0;
  std::vector<quote_t>::reverse_iterator it;

  for (it = quotes_.rbegin(); current_quote.timestamp - it->timestamp <=
                                  this->AVERAGE_TICK_PRICE_DELTA_PERIOD &&
                              it != quotes_.rend();
       it++) {

    double delta = abs(it->price - (it + 1)->price);
    total += delta;
    ticks++;
  }

  const double average = total / ticks;

  if (average > 1.0e6) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    const quote_t penultimate_quote = quotes_.at(quotes_.size() - 2);
    printf("Last Quote: %.2f • Last Price Delta: %.2f\n", current_quote.price,
           (current_quote.price - penultimate_quote.price));
    std::cout << fmt.reset << std::endl;

    return;
  }

  const double cumulative_max_sample_size = INFINITY;
  const double short_term_max_sample_size = 30;

  const double old_short_term_average =
      this->price_movements[symbol_]
          .short_term_three_minute_one_second_variance.average;

  const long int old_short_term_count =
      this->price_movements[symbol_]
          .short_term_three_minute_one_second_variance.count;

  const double short_term_average =
      ((old_short_term_average * old_short_term_count) + average) /
      (old_short_term_count + 1);

  const double old_cumulative_average =
      this->price_movements[symbol_].three_minute_one_second_variance.average;

  const long int old_cumulative_count =
      this->price_movements[symbol_].three_minute_one_second_variance.count;

  const double cumulative_average =
      ((old_cumulative_average * old_cumulative_count) + average) /
      (old_cumulative_count + 1);

  this->price_movements[symbol_].three_minute_one_second_variance.average =
      cumulative_average;

  this->price_movements[symbol_].three_minute_one_second_variance.count =
      std::min(cumulative_max_sample_size, (double)(old_cumulative_count + 1));

  this->price_movements[symbol_]
      .short_term_three_minute_one_second_variance.average = short_term_average;

  this->price_movements[symbol_]
      .short_term_three_minute_one_second_variance.count =
      std::min(short_term_max_sample_size, (double)(old_short_term_count + 1));

  write_price_movement(symbol_, this->price_movements[symbol_]);
}

#endif
