#if !defined ETRADE__STOCK_BOT_log_quote
#define ETRADE__STOCK_BOT_log_quote

/*
 * ETrade::StockBot
 * fmt
 * quote_t
 * quotes
 * symbol
 */
#include "stock_bot.h"

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float
#include <iomanip>             // std::setprecision
#include <iostream>            // std::cout, std::endl, std::fixed

void ETrade::StockBot::log_quote() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = quotes.size();

  if (!ticks) {
    return;
  }

  const quote_t *previous_quote = ticks > 1 ? &(quotes.at(ticks - 2)) : nullptr;
  const quote_t current_quote = quotes.back();

  if (previous_quote) {
    if (current_quote.current_price > previous_quote->current_price) {
      log_color = fmt.green;
    } else if (current_quote.current_price < previous_quote->current_price) {
      log_color = fmt.red;
    }
  }

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << log_color;
  std::cout << symbol << " Quote" << std::endl;
  std::cout << fmt.reset;
  std::cout << fmt.bold << log_color;
  std::cout << "Current Price: "
            << utils::float_::to_currency(current_quote.current_price)
            << std::endl;
  std::cout << "High: " << utils::float_::to_currency(current_quote.high)
            << std::endl;
  std::cout << "Low: " << utils::float_::to_currency(current_quote.low)
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
