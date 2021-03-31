#if !defined ETRADE__STOCK_BOT_fetch_quote
#define ETRADE__STOCK_BOT_fetch_quote

/*
 * ETrade::StockBot
 * SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS
 * etrade_client
 * quote_t
 * quotes
 * symbol
 */
#include "stock_bot.h"

#include "build_simple_moving_average.cpp" // build_simple_moving_average
#include <string>                          // std::string

void ETrade::StockBot::fetch_quote() {
  std::string quote_string = etrade_client.fetch_quote(symbol);
  quote_t current_quote = etrade_client.parse_quote(quote_string);
  current_quote.simple_moving_average =
      build_simple_moving_average(SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS);

  quotes.push_back(current_quote);
}

#endif
