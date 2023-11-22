#ifndef ALPACA__TAO_BOT_is_quote_stale
#define ALPACA__TAO_BOT_is_quote_stale

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt, quote_t
#include <iostream>           // std::cout, std::endl

bool Alpaca::TaoBot::is_quote_stale(const quote_t quote, const double epoch) {
  const bool is_stale = epoch - quote.timestamp > 3;

  const std::string epoch_string =
      ::utils::time_::date_string(epoch, "%H:%M %Z", "America/Chicago");

  const std::string quote_timestamp_string = ::utils::time_::date_string(
      quote.timestamp, "%H:%M %Z", "America/Chicago");

  if (is_stale) {
    std::cout << fmt.bold << fmt.yellow;
    printf("😪 Quote (%s) is stale at %s\n", quote_timestamp_string.c_str(),
           epoch_string.c_str());
    std::cout << fmt.reset;
  }

  return is_stale;
}

#endif
