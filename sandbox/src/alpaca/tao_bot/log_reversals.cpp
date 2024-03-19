#ifndef ALPACA__TAO_BOT_log_reversals
#define ALPACA__TAO_BOT_log_reversals

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, fmt, reversals_t, reversal_t
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf
#include <string>             // std::string

void Alpaca::TaoBot::log_reversals(reversals_t &reversals_) {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  if (!reversals_.timeframe_minutes) {
    return;
  }

  const int limit = 5;
  const int highs_n = reversals_.highs.size();
  const int lows_n = reversals_.lows.size();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("%i-Min 🔀 Reversals\n", reversals_.timeframe_minutes);
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.green;
  printf("Latest 5 of %i High(s):", highs_n);

  std::map<double, reversal_t>::reverse_iterator it = reversals_.highs.rbegin();
  int i = 0;

  for (; it != reversals_.highs.rend() && i < limit; it++, i++) {
    Formatted::Stream log_color = it->second.is_record ? fmt.yellow : fmt.green;
    const std::string all_time_text = it->second.is_running_record ? "🌟" : "";

    std::cout << log_color;

    printf(" %s%s",
           ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago")
               .c_str(),
           all_time_text.c_str());
  }

  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.red;
  printf("Latest 5 of %i Low(s): ", lows_n);

  it = reversals_.lows.rbegin();
  i = 0;

  for (; it != reversals_.lows.rend() && i < limit; it++, i++) {
    Formatted::Stream log_color = it->second.is_record ? fmt.yellow : fmt.red;
    const std::string all_time_text = it->second.is_running_record ? "🌟" : "";

    std::cout << log_color;

    printf(" %s%s",
           ::utils::time_::date_string(it->first, "%H:%M", "America/Chicago")
               .c_str(),
           all_time_text.c_str());
  }

  std::cout << fmt.bold << fmt.magenta << std::endl;
  printf("Record Highs: %i • Record Lows %i 🎯 %i\n",
         reversals_.record_counts["highs"], reversals_.record_counts["lows"],
         this->api_client.config.reversal_entry_delay);
  std::cout << fmt.reset << std::endl;
}

#endif
