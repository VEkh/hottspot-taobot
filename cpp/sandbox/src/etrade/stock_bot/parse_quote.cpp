#if !defined ETRADE__STOCK_BOT_parse_quote
#define ETRADE__STOCK_BOT_parse_quote

/*
 * ETrade::StockBot
 * quote_t
 * symbol
 */
#include "stock_bot.h"

#include "build_simple_moving_average.cpp" // build_simple_moving_average
#include "etrade/deps.cpp"                 // json
#include "etrade/types.cpp"                // ETrade::t
#include <string>                          // std::string
#include <time.h>                          // time, time_t

ETrade::t::quote_t
ETrade::StockBot::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  return {
      .current_price = full_quote["All"]["lastTrade"],
      .high = full_quote["All"]["high"],
      .low = full_quote["All"]["low"],
      .simple_moving_average =
          build_simple_moving_average(SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS),
      .symbol = symbol,
      .timestamp = now,
  };
}

#endif
