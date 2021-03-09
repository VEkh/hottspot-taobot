#if !defined ETRADE__STOCK_BOT_BETA_fetch_and_set_quote
#define ETRADE__STOCK_BOT_BETA_fetch_and_set_quote

/*
 * ETrade::StockBotBeta
 * etrade_client
 * fmt
 * quotes
 * symbol
 */
#include "stock_bot_beta.h"

#include "etrade/deps.cpp"    // json
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/json.cpp" // utils::json
#include <iostream>           // std::cout, std::endl
#include <string>             // std::string

void ETrade::StockBotBeta::fetch_and_set_quote() {
  Formatted::Stream log_color = fmt.yellow;

  std::string quote_string = etrade_client.fetch_quote(symbol);

  json current_quote = etrade_client.summarize_quote(quote_string);
  json logged_quote = utils::json::jslice(
      current_quote, {"currentPrice", "highPrice", "lowPrice"});

  if (!quotes.empty()) {
    json last_quote = quotes.back();

    if (current_quote["currentPrice"] > last_quote["currentPrice"]) {
      log_color = fmt.green;
    } else if (current_quote["currentPrice"] < last_quote["currentPrice"]) {
      log_color = fmt.red;
    }
  }

  quotes.push_back(current_quote);

  std::cout << fmt.bold << log_color << std::endl;
  std::cout << symbol << " quote: " << logged_quote << std::endl;
  std::cout << fmt.reset;
}

#endif
