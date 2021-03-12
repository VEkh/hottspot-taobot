#if !defined ETRADE__STOCK_BOT_BETA_parse_quote
#define ETRADE__STOCK_BOT_BETA_parse_quote

/*
 * ETrade::StockBotBeta
 * quote_t
 * symbol
 */
#include "stock_bot_beta.h"

#include "etrade/deps.cpp"           // json
#include "etrade/types.cpp"          // ETrade::t
#include "simple_moving_average.cpp" // simple_moving_average
#include <string>                    // std::string
#include <time.h>                    // time, time_t

ETrade::t::quote_t
ETrade::StockBotBeta::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  return {
      .current_price = full_quote["All"]["lastTrade"],
      .high = full_quote["All"]["high"],
      .low = full_quote["All"]["low"],
      .simple_moving_average =
          simple_moving_average(SIMPLE_MOVING_AVERAGE_PERIOD_TICKS),
      .symbol = symbol,
      .timestamp = now,
  };
}

#endif
