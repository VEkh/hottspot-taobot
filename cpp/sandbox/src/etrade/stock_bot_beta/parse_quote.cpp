#if !defined ETRADE__STOCK_BOT_BETA_parse_quote
#define ETRADE__STOCK_BOT_BETA_parse_quote

#include "etrade/deps.cpp"  // json
#include "stock_bot_beta.h" // ETrade::StockBotBeta, quote_t, symbol
#include <string>           // std::string
#include <time.h>           // time, time_t

ETrade::StockBotBeta::quote_t
ETrade::StockBotBeta::parse_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  return {
      .current_price = full_quote["All"]["lastTrade"],
      .high = full_quote["All"]["high"],
      .low = full_quote["All"]["low"],
      .simple_moving_average = 0.00,
      .symbol = symbol,
      .timestamp = now,
  };
}

#endif
