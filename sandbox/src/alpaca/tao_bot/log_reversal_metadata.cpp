#ifndef ALPACA__TAO_BOT_log_reversal_metadata
#define ALPACA__TAO_BOT_log_reversal_metadata

#include "day_range_percentile.cpp"  // day_range_percentile
#include "is_trending.cpp"           // is_trending
#include "lib/formatted.cpp"         // Formatted
#include "lib/utils/time.cpp"        // ::utils::time_
#include "stop_profit_type_name.cpp" // stop_profit_type_name
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

void Alpaca::TaoBot::log_reversal_metadata() {
  // TODO: Decide
  if (this->api_client.config.should_stop_profit && this->open_order_ptr) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Stop Profit Type: ");
    std::cout << fmt.cyan << stop_profit_type_name(this->open_order_ptr)
              << fmt.reset << std::endl;
  }

  // TODO: Decide
  const std::string trend_entry_text =
      this->api_client.config.should_enter_cis_trend ? "CIS" : "TRANS";

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Entry Direction: ");
  std::cout << fmt.cyan << trend_entry_text << std::endl;

  Formatted::Stream trend_status_color = fmt.cyan;
  std::string trend_status_text = "NONE";

  switch (this->current_trend.trend) {
  case trend_t::TREND_DOWN: {
    trend_status_color = fmt.red;
    trend_status_text = "DOWN";
    ;
    break;
  }
  case trend_t::TREND_UP: {
    trend_status_color = fmt.green;
    trend_status_text = "UP";
    break;
  }
  }

  if (is_trending()) {
    trend_status_text +=
        (" @ " + ::utils::time_::date_string(this->current_trend.at, "%H:%M",
                                             "America/Chicago"));
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Status: ");
  std::cout << trend_status_color << trend_status_text << std::endl;

  if (this->open_order_ptr && this->open_order_ptr->entry_reversal.at) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf("Open Position Entry Reversal\n");
    std::cout << fmt.reset;

    const reversal_t reversal = this->open_order_ptr->entry_reversal;

    if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      std::cout << fmt.bold << fmt.red;
      printf(
          "Low: %.2f p%.2f%% @ %s", reversal.mid,
          day_range_percentile(this->day_candle, reversal.mid),
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    } else {
      std::cout << fmt.bold << fmt.green;
      printf(
          "High: %.2f p%.2f%% @ %s", reversal.mid,
          day_range_percentile(this->day_candle, reversal.mid),
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    }

    std::cout << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
