#ifndef ALPACA__TAO_BOT_batch_volatility
#define ALPACA__TAO_BOT_batch_volatility

// NOTE: Deprecated

#include "deps.cpp"         // json
#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Alpaca::TaoBot, price_movement_t
#include <string>           // std::string
#include <vector>           // std::vector

double Alpaca::TaoBot::batch_volatility() {
  const std::vector<std::string> symbols =
      ::utils::io::tradeable_symbols("alpaca");

  double sum = 0;
  int count = 0;

  for (const std::string symbol_ : symbols) {
    const price_movement_t price_movement_ =
        this->quoter.read_price_movement(symbol_);

    if (!price_movement_.short_term_three_minute_one_second_variance.average) {
      continue;
    }

    if (!price_movement_.three_minute_one_second_variance.average) {
      continue;
    }

    const double short_term_average_one_sec_variance =
        price_movement_.short_term_three_minute_one_second_variance.average;

    const double average_one_sec_variance =
        price_movement_.three_minute_one_second_variance.average;

    const double volatility_ =
        short_term_average_one_sec_variance / average_one_sec_variance;
    sum += volatility_;
    count += 1;
  }

  if (!count) {
    return 0;
  }

  return sum / count;
}

#endif
