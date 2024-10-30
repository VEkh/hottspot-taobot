// TODO: Decide
#ifndef OANDA__TAO_BOT_log_spike_candles
#define OANDA__TAO_BOT_log_spike_candles

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "spike_score.cpp"    // spike_score // TODO: Decide
#include "tao_bot.h"          // Oanda::TaoBot, spike_candles_t, trend_t
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf

void Oanda::TaoBot::log_spike_candles() {
  candle_t current_candle = this->spike_candles.current;
  candle_t day_candle_ = this->spike_candles.day;
  candle_t previous_candle = this->spike_candles.previous;

  if (this->open_order_ptr) {
    current_candle = this->spike_candles.previous;
    previous_candle = this->spike_candles.penultimate;
  }

  const double day_range_percent =
      100.0 * current_candle.range() / day_candle_.range();

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🧨 Spike Candles\n");
  std::cout << fmt.reset;

  Formatted::Stream previous_color =
      previous_candle.trend() == trend_t::TREND_DOWN ? fmt.red : fmt.green;
  std::cout << fmt.bold << previous_color;
  printf("Previous => Open: %.5f @ %s • High: %.5f • Low: %.5f • Close: %.5f @ "
         "%s\n",
         previous_candle.open,
         ::utils::time_::date_string(previous_candle.opened_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str(),
         previous_candle.high, previous_candle.low, previous_candle.close,
         ::utils::time_::date_string(previous_candle.closed_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str());
  std::cout << fmt.reset;

  Formatted::Stream current_color =
      current_candle.trend() == trend_t::TREND_DOWN ? fmt.red : fmt.green;
  std::cout << fmt.bold << current_color;
  printf("Current  => Open: %.5f @ %s • High: %.5f • Low: %.5f • Close: %.5f @ "
         "%s\n",
         current_candle.open,
         ::utils::time_::date_string(current_candle.opened_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str(),
         current_candle.high, current_candle.low, current_candle.close,
         ::utils::time_::date_string(current_candle.closed_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str());
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.yellow;
  printf("Spike Score: %.2f • Spike Range as Day Range %%: %.2f%%\n",
         spike_score({
             .current = current_candle,
             .day = day_candle_,
             .penultimate = previous_candle,
             .previous = previous_candle,
         }),
         day_range_percent);
  std::cout << fmt.reset << std::endl;
}

#endif
