#ifndef ALPACA__TAO_BOT_log_reversal_metadata
#define ALPACA__TAO_BOT_log_reversal_metadata

#include "is_trending.cpp"    // is_trending
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h" // Alpaca::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

// TODO: Decide
#include "day_range_percentile.cpp" // day_range_percentile
#include <map>                      // std::map

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

  // TODO: Decide
  if (this->api_client.config.should_await_after_no_max_loss) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Await after no max loss? ✅\n");
  }

  // TODO: Decide
  Formatted::Stream await_trend_correction_color =
      this->api_client.config.should_trend_entry_await_correction ? fmt.green
                                                                  : fmt.red;

  std::string await_trend_correction_text =
      this->api_client.config.should_trend_entry_await_correction ? "YES"
                                                                  : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Await trend correction? ");
  std::cout << await_trend_correction_color << await_trend_correction_text
            << std::endl;

  // TODO: Decide
  if (!this->dynamic_trend_type.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Dynamic Trend Type: ");
    std::cout << fmt.cyan << this->dynamic_trend_type << std::endl;
  }

  // TODO: Decide
  if (this->api_client.config.non_init_reversing_stop_loss_ratio) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Non-init Reverse Stop Loss Ratio: ");
    std::cout << fmt.cyan
              << this->api_client.config.non_init_reversing_stop_loss_ratio
              << std::endl;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Peak Padding Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.peak_padding_ratio
            << std::endl;

  // TODO: Decide
  if (!this->api_client.config.reverse_profit_during.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Reverse profit during: ");
    std::cout << fmt.cyan << this->api_client.config.reverse_profit_during
              << std::endl;
  }

  // TODO: Decide
  if (!this->api_client.config.second_reversal_ref_type.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Second Reversal Ref Type: ");
    std::cout << fmt.cyan << this->api_client.config.second_reversal_ref_type
              << std::endl;
  }

  // TODO: Decide
  Formatted::Stream should_enter_at_record_color =
      this->api_client.config.should_trend_enter_at_record ? fmt.green
                                                           : fmt.red;

  std::string should_enter_at_record_text =
      this->api_client.config.should_trend_enter_at_record ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should trend enter at record? ");
  std::cout << should_enter_at_record_color << should_enter_at_record_text
            << std::endl;

  // TODO: Decide
  // TODO: Decide
  Formatted::Stream stop_profit_color =
      this->should_stop_profit ? fmt.green : fmt.red;

  std::string stop_profit_text = this->should_stop_profit ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Stop profit? ");
  std::cout << stop_profit_color << stop_profit_text << std::endl;

  // TODO: Decide
  if (this->api_client.config.should_toggle_dynamic_trend_type) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Toggle dynamic trend type? ✅\n");
  }

  // TODO: Decide
  if (this->should_stop_profit &&
      !this->api_client.config.stop_profit_tiers.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Max Profit-Stop Profit Timeframe Map: ");

    std::map<double, int> tiers = this->api_client.config.stop_profit_tiers;
    std::map<double, int>::iterator it;

    std::cout << fmt.magenta;
    for (it = tiers.begin(); it != tiers.end(); it++) {
      if (it != tiers.begin()) {
        printf(" • ");
      }

      printf("%.1f%%: %i min", it->first, it->second);
    }
    std::cout << std::endl;
  }

  // TODO: Decide
  if (this->api_client.config.trend_entry_percentile) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Trend Entry Percentile: ");
    std::cout << fmt.cyan;
    printf("%.2f\n", this->api_client.config.trend_entry_percentile);
  }

  // TODO: Decide
  if (this->api_client.config.trend_slip_percentile) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Trend Slip Percentile: ");
    std::cout << fmt.cyan;
    printf("%.2f\n", this->api_client.config.trend_slip_percentile);
  }

  // TODO: Decide
  if (this->win_percentile) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Win Percentile: ");
    std::cout << fmt.cyan;
    printf("%.2f\n", this->win_percentile);

    // TODO: Decide
    std::cout << fmt.bold << fmt.yellow;
    printf("Win Percentile Range: ");
    std::cout << fmt.cyan;
    printf("%s\n", this->api_client.config.win_percentile_range.c_str());
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
