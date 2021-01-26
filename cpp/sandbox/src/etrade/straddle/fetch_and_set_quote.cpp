#if !defined ETRADE__STRADDLE_fetch_and_set_quote
#define ETRADE__STRADDLE_fetch_and_set_quote

#include "etrade/deps.cpp"    // json
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/json.cpp" // utils::json
#include "straddle.h" // ETrade::Straddle, etrade_client, speedometer, stream_format, symbol
#include <iostream> // std::cout, std::endl
#include <string>   // std::string
#include <time.h>   // time, time_t

json quote_summary(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  json output = {
      {"beta", full_quote["All"]["beta"]},
      {"currentPrice", full_quote["All"]["lastTrade"]},
      {"highPrice", full_quote["All"]["high"]},
      {"lowPrice", full_quote["All"]["low"]},
      {"timestamp", now},
  };

  return output;
}

void ETrade::Straddle::fetch_and_set_quote() {
  Formatted::fmt_stream_t fmt = stream_format;
  Formatted::Stream log_color = fmt.yellow;

  std::string quote_string = etrade_client.fetch_quote(symbol);

  json current_quote = quote_summary(quote_string);
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
