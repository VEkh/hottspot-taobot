// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_reversals
#define ALPACA__TAO_BOT_log_reversals

#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/time.cpp"           // ::utils::time_
#include "nearest_opening_reversal.cpp" // nearest_opening_reversal
#include "tao_bot.h"                    // Alpaca::TaoBot, fmt, reversal_t
#include <algorithm>                    // std::max
#include <iostream>                     // std::cout, std::endl
#include <iterator>                     // std::advance
#include <list>                         // std::list
#include <stdio.h>                      // printf

void Alpaca::TaoBot::log_reversals() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const int count = 5;
  const int highs_n = this->reversals.highs.size();
  const int lows_n = this->reversals.lows.size();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🔀 Reversals\n");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.green;
  printf("Latest 5 of %i High(s):", highs_n);

  int start_index = std::max(highs_n - count, 0);
  std::list<reversal_t>::iterator it = this->reversals.highs.begin();
  std::advance(it, start_index);

  for (; it != this->reversals.highs.end(); it++) {
    printf(" %s",
           ::utils::time_::date_string(it->at, "%H:%M", "America/Chicago")
               .c_str());
  }

  std::cout << fmt.bold << fmt.magenta;
  printf(" Pending: %.2f @ %s", this->reversals.pending_high,
         ::utils::time_::date_string(this->reversals.pending_high_at, "%H:%M",
                                     "America/Chicago")
             .c_str());

  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.red;
  printf("Latest 5 of %i Low(s): ", lows_n);

  start_index = std::max(lows_n - count, 0);
  it = this->reversals.lows.begin();
  std::advance(it, start_index);

  for (; it != this->reversals.lows.end(); it++) {
    printf(" %s",
           ::utils::time_::date_string(it->at, "%H:%M", "America/Chicago")
               .c_str());
  }

  std::cout << fmt.bold << fmt.magenta;
  printf(" Pending: %.2f @ %s", this->reversals.pending_low,
         ::utils::time_::date_string(this->reversals.pending_low_at, "%H:%M",
                                     "America/Chicago")
             .c_str());

  if (this->open_order_ptr) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl
              << std::endl;
    printf("Open Position Reversal\n");
    std::cout << fmt.reset;

    const order_action_t action = this->open_order_ptr->action;
    const reversal_t reversal = nearest_opening_reversal(this->open_order_ptr);

    if (action == order_action_t::BUY) {
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
