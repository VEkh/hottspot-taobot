#if !defined ETRADE__STOCK_BOT_log_simple_moving_average
#define ETRADE__STOCK_BOT_log_simple_moving_average

/*
 * ETrade::StockBot
 * fmt
 * quote_t
 * quotes
 * sma_t
 */
#include "stock_bot.h"

#include "lib/formatted.cpp"     // Formatted
#include "lib/utils/float.cpp"   // utils::float
#include "lib/utils/integer.cpp" // utils::integer
#include <iomanip>               // std::setprecision
#include <iostream>              // std::cout, std::endl, std::fixed

void ETrade::StockBot::log_simple_moving_average() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote = ticks > 1 ? &(quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = quotes.back();
  const sma_t simple_moving_average = current_quote.simple_moving_average;

  if (previous_quote) {
    if (current_quote.simple_moving_average.price >
        previous_quote->simple_moving_average.price) {
      log_color = fmt.green;
    } else if (current_quote.simple_moving_average.price <
               previous_quote->simple_moving_average.price) {
      log_color = fmt.red;
    }
  }

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << log_color;
  std::cout << "Simple Moving Average ("
            << utils::integer_::seconds_to_clock(simple_moving_average.seconds)
            << ")" << std::endl;

  std::cout << fmt.reset;
  std::cout << fmt.bold << log_color;

  std::cout << "Price: "
            << utils::float_::to_currency(simple_moving_average.price)
            << " • Buy Δ: "
            << utils::float_::to_currency(simple_moving_average.buy_delta)
            << " • Sell Δ: "
            << utils::float_::to_currency(simple_moving_average.sell_delta)
            << std::endl;

  std::cout << "Buy Δ / Sell Δ: " << simple_moving_average.buy_sell_ratio
            << std::endl;
  std::cout << "Sell Δ / Buy Δ: " << simple_moving_average.sell_buy_ratio
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
