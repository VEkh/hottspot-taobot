#ifndef OANDA__TAO_BOT_log_reversal_metadata
#define OANDA__TAO_BOT_log_reversal_metadata

#include "day_range_percentile.cpp" // day_range_percentile
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "normalized_margin_multiplier.cpp" // normalized_margin_multiplier // TODO: Decide
#include "reverse_percentile.cpp"    // reverse_percentile
#include "stop_profit_type_name.cpp" // stop_profit_type_name
#include "tao_bot.h" // Oanda::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

void Oanda::TaoBot::log_reversal_metadata() {
  std::cout << fmt.bold << fmt.yellow;
  printf("Margin Multiplier: ");
  std::cout << fmt.cyan << normalized_margin_multiplier() << fmt.reset
            << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Margin Normalization Base %%: ");
  std::cout << fmt.cyan
            << this->api_client.config.margin_normalization_base_price_action *
                   100.0
            << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Market Duration Hours: ");
  std::cout << fmt.cyan << this->api_client.config.market_duration_hours
            << fmt.reset << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Normalized Account Loss Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.normalized_account_loss_ratio
            << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Reverse Percentile (%%): ");
  std::cout << fmt.cyan << reverse_percentile() << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Secondary Reverse Percentile: ");
  std::cout << fmt.cyan << this->api_client.config.secondary_reverse_percentile
            << fmt.reset << std::endl;

  Formatted::Stream should_await_record_break_color =
      this->api_client.config.should_await_record_break ? fmt.green : fmt.red;

  const std::string should_await_record_break_text =
      this->api_client.config.should_await_record_break ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should await record break? ");
  std::cout << should_await_record_break_color << should_await_record_break_text
            << fmt.reset << std::endl;

  Formatted::Stream should_enter_at_spike_color =
      this->api_client.config.should_enter_at_spike ? fmt.green : fmt.red;

  const std::string should_enter_at_spike_text =
      this->api_client.config.should_enter_at_spike ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should enter at spike? ");
  std::cout << should_enter_at_spike_color << should_enter_at_spike_text
            << fmt.reset << std::endl;

  if (this->api_client.config.should_enter_at_spike) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Spike Entry Score: ");
    std::cout << fmt.cyan << this->SPIKE_ENTRY_SCORE << fmt.reset << std::endl;

    std::cout << fmt.bold << fmt.yellow;
    printf("Spike Height Ratio: ");
    std::cout << fmt.cyan << this->SPIKE_HEIGHT_RATIO << fmt.reset << std::endl;
  }

  // TODO: Delete after ML switch
  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Loss Padding Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.stop_loss_padding_ratio
            << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Profit Target Price Action %%: ");
  std::cout << fmt.cyan
            << this->api_client.config.stop_profit_target_price_action
            << fmt.reset << std::endl;

  if (this->open_order_ptr) {
    std::cout << fmt.bold << fmt.yellow;
    printf("Stop Profit Type: ");
    std::cout << fmt.cyan << stop_profit_type_name(this->open_order_ptr)
              << fmt.reset << std::endl;
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Profit Version: ");
  std::cout << fmt.cyan << this->api_client.config.stop_profit_version
            << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Slip Percentile: ");
  std::cout << fmt.cyan << this->TREND_SLIP_PERCENTILE << fmt.reset
            << std::endl;

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

  trend_status_text +=
      (" @ " + ::utils::time_::date_string(this->current_trend.at,
                                           "%m/%d %R %Z", "America/Chicago"));

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Status: ");
  std::cout << trend_status_color << trend_status_text << std::endl;

  std::cout << fmt.bold << fmt.yellow;
  printf("Warm up period (hours): ");
  std::cout << fmt.cyan << this->api_client.config.warm_up_period_hours;
  std::cout << std::endl;

  if (this->open_order_ptr && this->open_order_ptr->entry_reversal.at) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf("Open Position Entry Reversal\n");
    std::cout << fmt.reset;

    const reversal_t reversal = this->open_order_ptr->entry_reversal;

    if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      std::cout << fmt.bold << fmt.red;
      printf("Low: %'.5f p%.2f%% @ %s", reversal.mid,
             day_range_percentile(this->day_candle, reversal.mid),
             ::utils::time_::date_string(reversal.at, "%m/%d %R %Z",
                                         "America/Chicago")
                 .c_str());
    } else {
      std::cout << fmt.bold << fmt.green;
      printf("High: %'.5f p%.2f%% @ %s", reversal.mid,
             day_range_percentile(this->day_candle, reversal.mid),
             ::utils::time_::date_string(reversal.at, "%m/%d %R %Z",
                                         "America/Chicago")
                 .c_str());
    }

    std::cout << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
