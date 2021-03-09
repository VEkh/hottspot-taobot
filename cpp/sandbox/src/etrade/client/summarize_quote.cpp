#if !defined ETRADE__CLIENT_summarize_quote
#define ETRADE__CLIENT_summarize_quote

#include "client.h"        // ETrade::Client
#include "etrade/deps.cpp" // json
#include <string>          // std::string
#include <time.h>          // time, time_t

json ETrade::Client::summarize_quote(const std::string &response_body) {
  time_t now;
  time(&now);

  json input = json::parse(response_body);
  json full_quote = input["QuoteResponse"]["QuoteData"].at(0);

  json output = {
      {"currentPrice", full_quote["All"]["lastTrade"]},
      {"highPrice", full_quote["All"]["high"]},
      {"lowPrice", full_quote["All"]["low"]},
      {"timestamp", now},
  };

  return output;
}

#endif
