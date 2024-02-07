// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_reversals
#define ALPACA__TAO_BOT_log_reversals

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversal_t, reversal_type_t
#include <algorithm> // std::max
#include <iostream>  // std::cout, std::endl
#include <iterator>  // std::advance
#include <list>      // std::list
#include <stdio.h>   // printf
#include <string>    // std::string
#include <utility>   // std::pair

void Alpaca::TaoBot::log_reversals() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const int count = 5;
  const int highs_n = this->reversals.highs.size();
  const int lows_n = this->reversals.lows.size();

  // TODO: Decide
  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("%i-Min 🔀 Reversals",
         this->api_client.config.reversal_timeframe_minutes);
  std::cout << fmt.reset;

  Formatted::Stream is_trending_color = this->is_trending ? fmt.green : fmt.red;
  const std::string is_trending_text = this->is_trending ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf(" Is trending? ");
  std::cout << is_trending_color << is_trending_text << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.green;
  printf("Latest 5 of %i High(s):", highs_n);

  int start_index = std::max(highs_n - count, 0);
  std::map<double, reversal_t>::iterator it = this->reversals.highs.begin();
  std::advance(it, start_index);

  for (; it != this->reversals.highs.end(); it++) {
    Formatted::Stream log_color = it->second.is_record ? fmt.yellow : fmt.green;

    std::cout << log_color;

    printf(" %s",
           ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago")
               .c_str());
  }

  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.red;
  printf("Latest 5 of %i Low(s): ", lows_n);

  start_index = std::max(lows_n - count, 0);
  it = this->reversals.lows.begin();
  std::advance(it, start_index);

  for (; it != this->reversals.lows.end(); it++) {
    Formatted::Stream log_color = it->second.is_record ? fmt.yellow : fmt.red;

    std::cout << log_color;

    printf(" %s",
           ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago")
               .c_str());
  }

  if (this->open_order_ptr) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl
              << std::endl;
    printf("Open Position Reversal\n");
    std::cout << fmt.reset;

    const reversal_t reversal = this->open_order_ptr->reversal;

    if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      std::cout << fmt.bold << fmt.red;
      printf(
          "Low: %.2f @ %s", reversal.mid,
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    } else {
      std::cout << fmt.bold << fmt.green;
      printf(
          "High: %.2f @ %s", reversal.mid,
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    }
  }

  std::cout << fmt.reset << std::endl << std::endl;
}

#endif
