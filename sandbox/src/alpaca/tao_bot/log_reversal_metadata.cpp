#ifndef ALPACA__TAO_BOT_log_reversal_metadata
#define ALPACA__TAO_BOT_log_reversal_metadata

#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/string.cpp" // ::utils::string
#include "lib/utils/time.cpp"   // ::utils::time_
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

void Alpaca::TaoBot::log_reversal_metadata() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return;
  }

  const int trend_toggle_n = this->api_client.config.toggle_is_trending_after_n;

  std::cout << fmt.bold << fmt.yellow;
  printf("Avg ⌚ Between Record Highs: %s • Lows: %s\n",
         ::utils::integer_::seconds_to_clock(
             this->reversals.avg_record_delta_seconds["highs"])
             .c_str(),
         ::utils::integer_::seconds_to_clock(
             this->reversals.avg_record_delta_seconds["lows"])
             .c_str());
  std::cout << fmt.reset;

  if (trend_toggle_n) {
    const int trend_loss_count = this->performance.trend_loss_count;

    Formatted::Stream trend_loss_count_color =
        trend_loss_count == trend_toggle_n ? fmt.green : fmt.red;

    Formatted::Stream is_trending_color =
        this->is_trending ? fmt.green : fmt.red;

    const std::string is_trending_text = this->is_trending ? "YES" : "NO";

    Formatted::Stream trend_strictness_color =
        this->api_client.config.is_trend_loss_strict ? fmt.green : fmt.red;

    const std::string trend_strictness_text =
        this->api_client.config.is_trend_loss_strict ? "YES" : "NO";

    std::cout << fmt.bold << fmt.yellow;
    printf("Trend-Indicating Losses: ");
    std::cout << trend_loss_count_color << trend_loss_count << " / "
              << trend_toggle_n << std::endl;

    std::cout << fmt.bold << fmt.yellow;
    printf("Is ");
    std::cout << fmt.cyan;
    std::cout << ::utils::string::upcase(
        this->api_client.config.trend_trigger_type);
    std::cout << fmt.yellow;
    printf(" trending? ");
    std::cout << is_trending_color << is_trending_text << std::endl;

    std::cout << fmt.bold << fmt.yellow;
    printf("Is trending strict? ");
    std::cout << trend_strictness_color << trend_strictness_text << std::endl;
  }

  if (this->open_order_ptr) {
    if (this->open_order_ptr->entry_reversal.at) {
      std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
      printf("Open Position Entry Reversal\n");
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

      std::cout << std::endl;
    }

    if (this->open_order_ptr->ref_reversal.at) {
      std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
      printf("Open Position Ref Reversal\n");
      std::cout << fmt.reset;

      const reversal_t reversal = this->open_order_ptr->ref_reversal;

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

      std::cout << std::endl;
    }
  }

  std::cout << fmt.reset << std::endl;
}

#endif
