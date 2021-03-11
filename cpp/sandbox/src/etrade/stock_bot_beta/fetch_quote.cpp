#if !defined ETRADE__STOCK_BOT_BETA_fetch_quote
#define ETRADE__STOCK_BOT_BETA_fetch_quote

/*
 * ETrade::StockBotBeta
 * etrade_client
 * quote_t
 * quotes
 * symbol
 */
#include "stock_bot_beta.h"

#include "parse_quote.cpp" // parse_quote
#include <string>          // std::string

void ETrade::StockBotBeta::fetch_quote() {
  std::string quote_string = etrade_client.fetch_quote(symbol);
  quote_t current_quote = parse_quote(quote_string);
  quotes.push_back(current_quote);
}

#endif
