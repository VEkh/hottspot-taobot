#ifndef OANDA__TAO_BOT_build_momentum_reversals
#define OANDA__TAO_BOT_build_momentum_reversals

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot, quote_t
#include <map>                // std::map
#include <string>             // std::string

void Oanda::TaoBot::build_momentum_reversals() {
  const int seek_time_milliseconds = 5 * 60 * 1e3;

  if (this->quotes.empty()) {
    return;
  }

  const quote_t first_quote = this->quotes.front();
  const quote_t last_quote = this->quotes.back();

  if (last_quote.timestamp - first_quote.timestamp <
      2 * seek_time_milliseconds) {
    return;
  }

  const int quotes_l = this->quotes.size();
  std::map<std::string, quote_t> resistance;
  std::map<std::string, quote_t> support;

  for (int current_i = 0; current_i < quotes_l; current_i++) {
    const quote_t current = this->quotes.at(current_i);

    if ((current.timestamp - first_quote.timestamp) < seek_time_milliseconds) {
      continue;
    }

    if ((last_quote.timestamp - current.timestamp) < seek_time_milliseconds) {
      continue;
    }

    bool is_peak = true, is_valley = true;

    for (int past_i = current_i - 1, future_i = current_i + 1;
         past_i > 0 && future_i < quotes_l; past_i--, future_i++) {
      const quote_t future = this->quotes.at(future_i);
      const quote_t past = this->quotes.at(past_i);

      if (is_peak) {
        is_peak = current.price >= future.price && current.price >= past.price;
      }

      if (is_valley) {
        is_valley =
            current.price <= future.price && current.price <= past.price;
      }

      if (!is_peak && !is_valley) {
        break;
      }

      if (current.timestamp - past.timestamp > seek_time_milliseconds &&
          future.timestamp - current.timestamp > seek_time_milliseconds) {
        break;
      }
    }

    const std::string key = ::utils::time_::date_string(
        current.timestamp / 1000, "%FT%R", "America/Chicago");

    if (is_peak) {
      resistance[key] = current;
    }

    if (is_valley) {
      support[key] = current;
    }
  }

  this->momentum_reversals["resistance"] = resistance;
  this->momentum_reversals["support"] = support;
}

#endif
