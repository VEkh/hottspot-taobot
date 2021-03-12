#if !defined ETRADE__STOCK_BOT_fetch_and_set_quote
#define ETRADE__STOCK_BOT_fetch_and_set_quote

#include "log_quote.cpp"   // log_quote
#include "parse_quote.cpp" // parse_quote
#include "stock_bot.h" // ETrade::StockBot, etrade_client, stream_format, symbol
#include <string>      // std::string

void ETrade::StockBot::fetch_and_set_quote() {
  std::string quote_string = etrade_client.fetch_quote(symbol);
  quote_t current_quote = parse_quote(quote_string);
  quotes.push_back(current_quote);
  log_quote();
}

#endif
