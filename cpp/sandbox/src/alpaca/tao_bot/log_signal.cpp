#ifndef ALPACA__TAO_BOT_log_signal
#define ALPACA__TAO_BOT_log_signal

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 */
#include "tao_bot.h"

#include "converted_signaler_price.cpp" // converted_signaler_price
#include "current_price.cpp"            // current_price
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/float.cpp"          // ::utils::float_
#include "lib/utils/integer.cpp"        // ::utils::integer_
#include "lib/utils/string.cpp"         // ::utils::string
#include <ctime>                        // std::time
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // printf

void Alpaca::TaoBot::log_signal(const signal_t &signal, const char *title) {
  if (signal.signaler.empty()) {
    return;
  }

  Formatted::Stream log_color =
      signal.signaler_trend_direction == order_action_t::BUY ? fmt.green
                                                             : fmt.red;
  const double signaled_price = current_price(signal.signaled);
  const double signaler_price = converted_signaler_price(signal);
  const char *trend_direction =
      Alpaca::constants::ORDER_ACTIONS[signal.signaler_trend_direction];
  const int trend_duration =
      std::time(nullptr) - signal.signaler_trend_started_at;

  const double price_delta_ratio =
      (signaler_price - signaled_price) / signaled_price;

  std::cout << fmt.bold << fmt.underline << log_color;
  printf("%s Signal\n", title);

  std::cout << fmt.reset << fmt.bold << log_color;

  printf("Signaled [%s]: $%'.2f • Signaler [%s] (in Signaled): $%'.2f "
         "(%+.2f%%)\n"
         "Trend Direction: %s • Trend Duration: %s\n",
         signal.signaled.c_str(), ::utils::float_::to_currency(signaled_price),
         signal.signaler.c_str(), ::utils::float_::to_currency(signaler_price),
         price_delta_ratio * 100.0,
         ::utils::string::upcase(trend_direction).c_str(),
         ::utils::integer_::seconds_to_clock(trend_duration).c_str());

  std::cout << fmt.reset << std::endl;
}

#endif
