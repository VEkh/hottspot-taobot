#ifndef ALPACA__TAO_BOT_batch_volatility
#define ALPACA__TAO_BOT_batch_volatility

#include "deps.cpp"                // json
#include "lib/utils/io.cpp"        // ::utils::io
#include "load_price_movement.cpp" // load_price_movement
#include "tao_bot.h"               // Alpaca::TaoBot
#include <string>                  // std::string
#include <vector>                  // std::vector

double Alpaca::TaoBot::batch_volatility() {
  const std::vector<std::string> symbols =
      ::utils::io::tradeable_symbols("alpaca");

  double sum = 0;
  int count = 0;

  for (const std::string symbol_ : symbols) {
    json price_movement_json = load_price_movement(symbol_);

    if (price_movement_json.empty()) {
      continue;
    }

    if (!price_movement_json.contains(
            "short_term_three_minute_one_second_variance")) {
      continue;
    }

    if (!price_movement_json.contains("three_minute_one_second_variance")) {
      continue;
    }

    const double short_term_average_one_sec_variance =
        price_movement_json["short_term_three_minute_one_second_variance"]
                           ["average"];

    const double average_one_sec_variance =
        price_movement_json["three_minute_one_second_variance"]["average"];

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
