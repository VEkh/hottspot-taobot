// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_reversals
#define ALPACA__TAO_BOT_log_reversals

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversals_t, reversal_t, reversal_type_t
#include <algorithm> // std::max
#include <iostream>  // std::cout, std::endl
#include <iterator>  // std::advance
#include <list>      // std::list
#include <stdio.h>   // printf
#include <string>    // std::string
#include <utility>   // std::pair

void Alpaca::TaoBot::log_reversals(reversals_t &reversals_) {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  if (!reversals_.timeframe_minutes) {
    return;
  }

  const int count = 5;
  const int highs_n = reversals_.highs.size();
  const int lows_n = reversals_.lows.size();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("%i-Min 🔀 Reversals", reversals_.timeframe_minutes);
  std::cout << fmt.reset;

  // TODO: Decide
  const int trend_loss_count = this->performance.trend_loss_count;

  Formatted::Stream trend_loss_count_color =
      trend_loss_count == this->api_client.config.toggle_is_trending_after_n
          ? fmt.green
          : fmt.red;

  std::cout << fmt.bold << fmt.yellow;
  printf(" Trend-Indicating Losses: ");
  std::cout << trend_loss_count_color << trend_loss_count << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.green;
  printf("Latest 5 of %i High(s):", highs_n);

  int start_index = std::max(highs_n - count, 0);
  std::map<double, reversal_t>::iterator it = reversals_.highs.begin();
  std::advance(it, start_index);

  for (; it != reversals_.highs.end(); it++) {
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
  it = reversals_.lows.begin();
  std::advance(it, start_index);

  for (; it != reversals_.lows.end(); it++) {
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

    const reversal_t reversal = this->open_order_ptr->entry_reversal;

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
