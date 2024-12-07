#ifndef OANDA__TAO_BOT_log_reversal_metadata
#define OANDA__TAO_BOT_log_reversal_metadata

#include "day_range_percentile.cpp" // day_range_percentile
#include "is_trending.cpp"          // is_trending
#include "lib/formatted.cpp"        // Formatted
#include "lib/utils/time.cpp"       // ::utils::time_
#include "ready_to_stop_loss.cpp"   // ready_to_stop_loss // TODO: Decide
#include "tao_bot.h" // Oanda::TaoBot, fmt, reversal_t, reversal_type_t
#include <iostream>  // std::cout, std::endl
#include <stdio.h>   // printf
#include <string>    // std::string

#include "stop_loss_reversals_name.cpp" // TODO: Decide

void Oanda::TaoBot::log_reversal_metadata() {
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
        (" @ " + ::utils::time_::date_string(this->current_trend.at,
                                             "%m/%d %R %Z", "America/Chicago"));
  }

  std::cout << fmt.bold << fmt.yellow;
  printf("Trend Status: ");
  std::cout << trend_status_color << trend_status_text << std::endl;

  // TODO: Decide
  Formatted::Stream is_entry_reversal_color =
      this->is_entry_reversal ? fmt.green : fmt.red;
  const std::string is_entry_reversal_text =
      this->is_entry_reversal ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Is entry reversal? ");
  std::cout << is_entry_reversal_color << is_entry_reversal_text << fmt.reset
            << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Market Duration Hours: ");
  std::cout << fmt.cyan << this->api_client.config.market_duration_hours
            << fmt.reset << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Reversal Proximity Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.reversal_proximity_ratio
            << fmt.reset << std::endl;

  // TODO: Decide
  Formatted::Stream should_only_reverse_loss_color =
      this->api_client.config.should_only_reverse_loss ? fmt.green : fmt.red;
  const std::string should_only_reverse_loss_text =
      this->api_client.config.should_only_reverse_loss ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should only reverse loss? ");
  std::cout << should_only_reverse_loss_color << should_only_reverse_loss_text
            << fmt.reset << std::endl;

  // TODO: Decide
  Formatted::Stream should_reverse_profit_color =
      this->api_client.config.should_reverse_profit ? fmt.green : fmt.red;
  const std::string should_reverse_profit_text =
      this->api_client.config.should_reverse_profit ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should reverse profit? ");
  std::cout << should_reverse_profit_color << should_reverse_profit_text
            << fmt.reset << std::endl;

  // TODO: Decide
  Formatted::Stream should_stop_profit_color =
      this->api_client.config.should_stop_profit ? fmt.green : fmt.red;
  const std::string should_stop_profit_text =
      this->api_client.config.should_stop_profit ? "YES" : "NO";

  std::cout << fmt.bold << fmt.yellow;
  printf("Should stop profit? ");
  std::cout << should_stop_profit_color << should_stop_profit_text << fmt.reset
            << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Loss Padding Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.stop_loss_padding_ratio
            << fmt.reset << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Loss Reversals: ");
  std::cout << fmt.cyan << ::utils::string::upcase(stop_loss_reversals_name())
            << fmt.reset << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Profit Day Range Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.stop_profit_day_range_ratio
            << fmt.reset << std::endl;

  // TODO: Decide
  std::cout << fmt.bold << fmt.yellow;
  printf("Stop Profit Ratio: ");
  std::cout << fmt.cyan << this->api_client.config.stop_profit_ratio
            << fmt.reset << std::endl;

  // TODO: Decide
  if (!this->api_client.config.should_immediately_stop_loss) {
    const bool ready_to_stop_loss_ = ready_to_stop_loss();

    Formatted::Stream ready_to_stop_loss_color =
        ready_to_stop_loss_ ? fmt.green : fmt.red;

    const std::string ready_to_stop_loss_text =
        ready_to_stop_loss_ ? "YES" : "NO";

    std::cout << fmt.bold << fmt.yellow;
    printf("Ready to stop loss? ");
    std::cout << ready_to_stop_loss_color << ready_to_stop_loss_text
              << fmt.reset << std::endl;
  }

  // TODO: Decide
  if (this->context_entry_reversal.mid) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf("Context Reversal\n");
    std::cout << fmt.reset;

    Formatted::Stream context_entry_reversal_color =
        this->context_entry_reversal.type == reversal_type_t::REVERSAL_LOW
            ? fmt.green
            : fmt.red;

    const std::string context_entry_reversal_type =
        this->context_entry_reversal.type == reversal_type_t::REVERSAL_LOW
            ? "Low"
            : "High";

    std::cout << fmt.bold << context_entry_reversal_color;
    printf("%s @ %s", context_entry_reversal_type.c_str(),
           ::utils::time_::date_string(this->context_entry_reversal.at,
                                       "%m/%d %R %Z", "America/Chicago")
               .c_str());
    std::cout << fmt.reset << std::endl;
  }

  if (this->open_order_ptr && this->open_order_ptr->entry_reversal.at) {
    std::cout << fmt.bold << fmt.magenta << fmt.underline << std::endl;
    printf("Open Position Entry Reversal\n");
    std::cout << fmt.reset;

    const reversal_t reversal = this->open_order_ptr->entry_reversal;

    if (reversal.type == reversal_type_t::REVERSAL_LOW) {
      std::cout << fmt.bold << fmt.red;
      printf("Low: %'.5f p%.2f%% @ %s", reversal.mid,
             day_range_percentile(reversal.mid),
             ::utils::time_::date_string(reversal.at, "%m/%d %R %Z",
                                         "America/Chicago")
                 .c_str());
    } else {
      std::cout << fmt.bold << fmt.green;
      printf("High: %'.5f p%.2f%% @ %s", reversal.mid,
             day_range_percentile(reversal.mid),
             ::utils::time_::date_string(reversal.at, "%m/%d %R %Z",
                                         "America/Chicago")
                 .c_str());
    }

    std::cout << std::endl;
  }

  std::cout << fmt.reset << std::endl;
}

#endif
