#ifndef ALPACA__QUOTE_set_price_movement
#define ALPACA__QUOTE_set_price_movement

#include "quote.h" // Alpaca::Quote, quote_t
#include <math.h>  // abs, INFINITY
#include <string>  // std::string
#include <vector>  // std::vector

void Alpaca::Quote::set_price_movement(const std::string symbol) {
  if (!this->quotes[symbol].size()) {
    return;
  }

  const quote_t current_quote = this->quotes[symbol].back();

  if (current_quote.timestamp - this->quotes[symbol].front().timestamp <
      this->AVG_ONE_SEC_VARIANCE_TIMEFRAME) {
    return;
  }

  double total = 0;
  int ticks = 0;
  std::vector<quote_t>::reverse_iterator it;

  for (it = this->quotes[symbol].rbegin();
       current_quote.timestamp - it->timestamp <=
           this->AVG_ONE_SEC_VARIANCE_TIMEFRAME &&
       it != this->quotes[symbol].rend();
       it++) {

    const double time_delta = it->timestamp - (it + 1)->timestamp;
    const double delta = (it->price - (it + 1)->price) / time_delta;

    total += abs(delta);
    ticks++;
  }

  const double average = total / ticks;

  if (average > 1.0e6) {
    std::cout << fmt.bold << fmt.yellow;
    puts("🧐 STRANGE PRICE MOVEMENT");
    const quote_t penultimate_quote =
        this->quotes[symbol].at(this->quotes[symbol].size() - 2);
    printf("Last Quote: %.2f • Last Price Delta: %.2f\n", current_quote.price,
           (current_quote.price - penultimate_quote.price));
    std::cout << fmt.reset << std::endl;

    return;
  }

  const double cumulative_max_sample_size = this->PRICE_MOVEMENT_SAMPLE_SIZE;
  const double short_term_max_sample_size = 30;

  const double old_short_term_average =
      this->price_movements[symbol]
          .short_term_three_minute_one_second_variance.average;

  const long int old_short_term_count =
      this->price_movements[symbol]
          .short_term_three_minute_one_second_variance.count;

  const double short_term_average =
      ((old_short_term_average * old_short_term_count) + average) /
      (old_short_term_count + 1);

  const double old_cumulative_average =
      this->price_movements[symbol].three_minute_one_second_variance.average;

  const long int old_cumulative_count =
      this->price_movements[symbol].three_minute_one_second_variance.count;

  const double cumulative_average =
      ((old_cumulative_average * old_cumulative_count) + average) /
      (old_cumulative_count + 1);

  if ((average / old_cumulative_average) >= 0.33) {
    this->price_movements[symbol].three_minute_one_second_variance.average =
        cumulative_average;

    this->price_movements[symbol].three_minute_one_second_variance.count =
        std::min(cumulative_max_sample_size,
                 (double)(old_cumulative_count + 1));
  }

  this->price_movements[symbol]
      .short_term_three_minute_one_second_variance.average = short_term_average;

  this->price_movements[symbol]
      .short_term_three_minute_one_second_variance.count =
      std::min(short_term_max_sample_size, (double)(old_short_term_count + 1));
}

#endif
