#ifndef ALPACA__TAO_BOT_log_reversal_metadata
#define ALPACA__TAO_BOT_log_reversal_metadata

#include "day_range_percentile.cpp" // day_range_percentile
#include "is_trending.cpp"          // is_trending
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

void Alpaca::TaoBot::log_reversal_metadata() {
  Formatted::Stream trend_status_color = fmt.cyan;
  std::string trend_status_text = "REVERSING";

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

  if (!this->dynamic_trend_type.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Dynamic Trend Type: ");
    std::cout << fmt.cyan << this->dynamic_trend_type << std::endl;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Peak Padding Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.peak_padding_ratio
            << std::endl;

  if (!this->api_client.config.reverse_profit_during.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Reverse profit during: ");
    std::cout << fmt.cyan << this->api_client.config.reverse_profit_during
              << std::endl;
  }

  // TODO: Decide
  Formatted::Stream asymmetric_reversal_color =
      this->api_client.config.should_await_asymmetric_reversal ? fmt.green
                                                               : fmt.red;

  const std::string asymmetric_reversal_text =
      this->api_client.config.should_await_asymmetric_reversal ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should await asymmetric reversal? ");
  std::cout << asymmetric_reversal_color << asymmetric_reversal_text
            << std::endl;

  // TODO: Decide
  Formatted::Stream symmetric_reversal_color =
      this->api_client.config.should_await_symmetric_reversal ? fmt.green
                                                              : fmt.red;

  const std::string symmetric_reversal_text =
      this->api_client.config.should_await_symmetric_reversal ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should await symmetric reversal? ");
  std::cout << symmetric_reversal_color << symmetric_reversal_text << std::endl;

  // TODO: Decide
  Formatted::Stream should_hold_first_position_color =
      this->api_client.config.should_hold_first_position ? fmt.green : fmt.red;

  const std::string should_hold_first_position_text =
      this->api_client.config.should_hold_first_position ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should hold first position? ");
  std::cout << should_hold_first_position_color
            << should_hold_first_position_text << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Slip Percentile: ");
  std::cout << fmt.cyan;
  printf("%.2f\n", this->api_client.config.trend_slip_percentile
                       ? this->api_client.config.trend_slip_percentile
                       : this->EQUATOR_PERCENTILE);

  if (this->api_client.config.win_percentile) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Win Percentile: ");
    std::cout << fmt.cyan;
    printf("%.2f\n", this->api_client.config.win_percentile);
  }

  if (this->open_order_ptr && this->open_order_ptr->entry_reversal.at) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf("Open Position Entry Reversal\n");
    std::cout << fmt.reset;

    const reversal_t reversal = this->open_order_ptr->entry_reversal;

    if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      std::cout << fmt.bold << fmt.red;
      printf(
          "Low: %.2f p%.2f%% @ %s", reversal.mid,
          day_range_percentile(reversal.mid),
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    } else {
      std::cout << fmt.bold << fmt.green;
      printf(
          "High: %.2f p%.2f%% @ %s", reversal.mid,
          day_range_percentile(reversal.mid),
          ::utils::time_::date_string(reversal.at, "%H:%M", "America/Chicago")
              .c_str());
    }

    std::cout << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
