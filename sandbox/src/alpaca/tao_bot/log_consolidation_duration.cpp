// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_consolidation_duration
#define ALPACA__TAO_BOT_log_consolidation_duration

#include "candles_range.cpp"    // candles_range
#include "current_mid.cpp"      // current_mid
#include "is_consolidating.cpp" // is_consolidating
#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/time.cpp"   // ::utils::time_
#include "tao_bot.h"            // Alpaca::TaoBot, candle_t, fmt, trend_t
#include <iostream>             // std::cout, std::endl
#include <list>                 // std::list
#include <stdio.h>              // printf

void Alpaca::TaoBot::log_consolidation_duration() {
  const int range_n = this->api_client.config.consolidation_duration_mintues;

  if (range_n > this->latest_candles.size()) {
    return;
  }

  const int half_range_n = range_n / 2;
  const bool is_consolidating_ = is_consolidating();

  const int first_range_start_index = this->latest_candles.size() - range_n;
  const int second_range_start_index =
      this->latest_candles.size() - range_n + half_range_n;

  range_t first_half_range =
      candles_range(first_range_start_index, half_range_n);

  range_t second_half_range =
      candles_range(second_range_start_index, half_range_n);

  Formatted::Stream is_consolidating_color =
      is_consolidating_ ? fmt.green : fmt.red;

  const std::string is_consolidating_text = is_consolidating_ ? "YES" : "NO";

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🔥 Latest %i %i-Min Candles (%s -> %s)", range_n,
         this->db_candle.duration_minutes,
         ::utils::time_::date_string(first_half_range.opened_at, "%H:%M",
                                     "America/Chicago")
             .c_str(),
         ::utils::time_::date_string(second_half_range.closed_at, "%H:%M",
                                     "America/Chicago")
             .c_str());

  const char *active_consolidation_char =
      range_n == this->active_consolidation_duration_minutes ? " 🌟" : "";
  std::cout << fmt.no_underline;
  std::cout << fmt.yellow;
  printf(" Consolidating: ");
  std::cout << is_consolidating_color << is_consolidating_text
            << active_consolidation_char;
  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("🥇 ");
  std::cout << fmt.green;
  printf("High: %.2f ", first_half_range.high);
  std::cout << fmt.red;
  printf("Low: %.2f ", first_half_range.low);
  std::cout << fmt.yellow;
  printf("Δ: %.2f\n", first_half_range.delta());
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.yellow;
  printf("🥈 ");
  std::cout << fmt.green;
  printf("High: %.2f ", second_half_range.high);
  std::cout << fmt.red;
  printf("Low: %.2f ", second_half_range.low);
  std::cout << fmt.yellow;
  printf("Δ: %.2f\n", second_half_range.delta());
  std::cout << fmt.reset;

  if (this->open_order_ptr) {
    range_t range = this->open_order_ptr->consolidation_range;
    const double mid = current_mid();

    std::string in_range_check_char = " ✅";

    if (mid > range.high) {
      in_range_check_char = " 👆";
    } else if (mid < range.low) {
      in_range_check_char = " 👇";
    }

    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf(
        "Open Position Consolidation (%s -> %s)\n",
        ::utils::time_::date_string(range.opened_at, "%H:%M", "America/Chicago")
            .c_str(),
        ::utils::time_::date_string(range.closed_at, "%H:%M", "America/Chicago")
            .c_str());
    std::cout << fmt.reset;

    std::cout << fmt.bold << fmt.green;
    printf("High: %.2f ", range.high);
    std::cout << fmt.red;
    printf("Low: %.2f ", range.low);
    std::cout << fmt.yellow;
    printf("Δ: %.2f%s\n", range.delta(), in_range_check_char.c_str());
    std::cout << fmt.reset;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
