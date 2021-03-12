#if !defined ETRADE__STOCK_BOT_fetch_quote
#define ETRADE__STOCK_BOT_fetch_quote

/*
 * ETrade::StockBot
 * etrade_client
 * quote_t
 * quotes
 * symbol
 */
#include "stock_bot.h"

#include "parse_quote.cpp" // parse_quote
#include <string>          // std::string

void ETrade::StockBot::fetch_quote() {
  std::string quote_string = etrade_client.fetch_quote(symbol);
  quote_t current_quote = parse_quote(quote_string);
  quotes.push_back(current_quote);
}

#endif
