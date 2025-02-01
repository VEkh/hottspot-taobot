// TODO: Decide
#ifndef ALPACA__TAO_BOT_log_spike_candles
#define ALPACA__TAO_BOT_log_spike_candles

#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "spike_score.cpp"    // spike_score
#include "tao_bot.h"          // Alpaca::TaoBot, spike_candles_t, trend_t
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf

void Alpaca::TaoBot::log_spike_candles() {
  // TODO: Decide
  if (!this->api_client.config.should_enter_at_spike) {
    return;
  }

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
  printf("🧨 Spike %i-Min Candles",
         this->api_client.config.spike_duration_minutes);
  std::cout << fmt.reset << std::endl;

  Formatted::Stream previous_color =
      previous_candle.trend() == trend_t::TREND_DOWN ? fmt.red : fmt.green;
  std::cout << fmt.bold << previous_color;
  printf("Previous => Open: %.2f @ %s • High: %.2f • Low: %.2f • Close: %.2f @ "
         "%s",
         previous_candle.open,
         ::utils::time_::date_string(previous_candle.opened_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str(),
         previous_candle.high, previous_candle.low, previous_candle.close,
         ::utils::time_::date_string(previous_candle.closed_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str());
  std::cout << fmt.reset << std::endl;

  Formatted::Stream current_color =
      current_candle.trend() == trend_t::TREND_DOWN ? fmt.red : fmt.green;
  std::cout << fmt.bold << current_color;
  printf("Current  => Open: %.2f @ %s • High: %.2f • Low: %.2f • Close: %.2f @ "
         "%s",
         current_candle.open,
         ::utils::time_::date_string(current_candle.opened_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str(),
         current_candle.high, current_candle.low, current_candle.close,
         ::utils::time_::date_string(current_candle.closed_at, "%m/%d %R",
                                     "America/Chicago")
             .c_str());
  std::cout << fmt.reset << std::endl;

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
