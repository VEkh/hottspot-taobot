#if !defined ETRADE__STOCK_BOT_BETA_log_quote
#define ETRADE__STOCK_BOT_BETA_log_quote

/*
 * ETrade::StockBotBeta
 * etrade_client
 * fmt
 * quote_t
 * quotes
 * symbol
 */
#include "stock_bot_beta.h"

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float::to_currency
#include "parse_quote.cpp"     // parse_quote
#include <iomanip>             // std::setprecision
#include <iostream>            // std::cout, std::endl, std::fixed
#include <string>              // std::string

void ETrade::StockBotBeta::log_quote() {
  Formatted::Stream log_color = fmt.yellow;
  const int ticks = quotes.size();

  if (!ticks) {
    return;
  }

  quote_t *previous_quote = ticks > 1 ? &(quotes.at(ticks - 2)) : nullptr;
  quote_t current_quote = quotes.back();

  if (previous_quote) {
    if (current_quote.current_price > previous_quote->current_price) {
      log_color = fmt.green;
    } else if (current_quote.current_price < previous_quote->current_price) {
      log_color = fmt.red;
    }
  }

  std::cout << std::setprecision(2) << std::fixed;
  std::cout << fmt.bold << fmt.underline << log_color;
  std::cout << symbol << " Quote:" << std::endl;
  std::cout << fmt.reset;
  std::cout << fmt.bold << log_color;
  std::cout << "Current Price: "
            << utils::float_::to_currency(current_quote.current_price)
            << std::endl;
  std::cout << "High: " << utils::float_::to_currency(current_quote.high)
            << std::endl;
  std::cout << "Low: " << utils::float_::to_currency(current_quote.low)
            << std::endl;
  std::cout << "Simple Moving Average: "
            << utils::float_::to_currency(current_quote.simple_moving_average)
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
