#if !defined ETRADE__STOCK_BOT_set_and_log_simple_moving_average
#define ETRADE__STOCK_BOT_set_and_log_simple_moving_average

/*
 * ETrade::StockBot
 * fmt
 * quote_t
 * quotes
 * sma_t
 */
#include "stock_bot.h"

#include "compute_moving_buy_sell_ratio_average.cpp" // compute_moving_buy_sell_ratio_average
#include "lib/formatted.cpp"                         // Formatted
#include "lib/utils/float.cpp"                       // utils::float
#include "lib/utils/integer.cpp"                     // utils::integer_
#include "stock_bot.h"                               // ETrade::StockBot
#include <iomanip>                                   // std::setprecision
#include <iostream> // std::cout, std::endl, std::fixed
#include <vector>   // std::vector

void ETrade::StockBot::set_and_log_simple_moving_average() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote = ticks > 1 ? &(quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = quotes.back();
  const sma_t simple_moving_average = current_quote.simple_moving_average;

  int long_period_seconds = 5 * 60;
  int short_period_seconds = 0.5 * 60;
  std::vector<int> moving_average_periods = {
      short_period_seconds,
      long_period_seconds,
  };

  std::map<int, std::map<const char *, double>> average_buy_sell_ratios =
      compute_moving_buy_sell_ratio_average(moving_average_periods);

  this->long_average_buy_sell_ratio =
      average_buy_sell_ratios[long_period_seconds]["buy"];
  this->long_average_sell_buy_ratio =
      average_buy_sell_ratios[long_period_seconds]["sell"];

  this->short_average_buy_sell_ratio =
      average_buy_sell_ratios[short_period_seconds]["buy"];
  this->short_average_sell_buy_ratio =
      average_buy_sell_ratios[short_period_seconds]["sell"];

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

  for (int period : moving_average_periods) {
    std::cout << "Avg. Buy Δ / Sell Δ ("
              << utils::integer_::seconds_to_clock(period)
              << "): " << average_buy_sell_ratios[period]["buy"] << std::endl;
    std::cout << "Avg. Sell Δ / Buy Δ ("
              << utils::integer_::seconds_to_clock(period)
              << "): " << average_buy_sell_ratios[period]["sell"] << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
