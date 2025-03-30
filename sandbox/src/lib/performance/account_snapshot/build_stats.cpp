#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_build_stats
#define PERFORMANCE__ACCOUNT_SNAPSHOT_build_stats

#include "account_snapshot.h" // Performance::AccountSnapshot, account_snapshot_t, fmt
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include <iostream>           // std::cout, std::endl
#include <list>               // std::list
#include <stdexcept>          // std::invalid_argument
#include <stdio.h>            // printf
#include <string>             // std::string

void Performance::AccountSnapshot::build_stats(
    std::list<account_snapshot_t> &snapshots) {
  if (snapshots.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Failed to read snapshots for %s.",
           this->config.api_key_id.c_str());
    std::cout << fmt.reset << std::endl;

    throw std::invalid_argument("");
  }

  this->stats.original_snapshot = snapshots.front();

  for (std::list<account_snapshot_t>::iterator it = snapshots.begin();
       it != snapshots.end(); it++) {
    const account_snapshot_t snapshot = *it;

    const double current_equity = snapshot.equity;
    const double max_equity = snapshot.max_equity;
    const double max_equity_timestamp = snapshot.max_equity_timestamp;
    const double min_equity = snapshot.min_equity;
    const double min_equity_timestamp = snapshot.min_equity_timestamp;
    const double original_equity = snapshot.original_equity;

    const double current_profit = current_equity - original_equity;
    const double current_profit_percent =
        100 * (current_equity - original_equity) / original_equity;
    const double min_profit = min_equity - original_equity;
    const double min_profit_ratio =
        (min_equity - original_equity) / original_equity;
    const double min_profit_percent = 100 * min_profit_ratio;
    const double max_profit = max_equity - original_equity;
    const double max_profit_ratio =
        (max_equity - original_equity) / original_equity;
    const double max_profit_percent = 100 * max_profit_ratio;

    if (current_profit > 0) {
      this->stats.daily_win_max_equity_ratios.push_back(max_profit_ratio);
      this->stats.daily_win_min_equity_ratios.push_back(min_profit_ratio);
    }

    this->stats.daily_net_pl_ratio += current_profit / original_equity;
    this->stats.net_pl += current_profit;

    if (max_equity != original_equity || min_equity != original_equity) {
      this->stats.day_count++;
    }
    this->stats.loss_count += (int)current_profit < 0;
    this->stats.win_count += (int)current_profit >= 0;

    Formatted::Stream profit_color = current_profit >= 0 ? fmt.green : fmt.red;

    const std::string snapshot_time =
        ::utils::time_::date_string(snapshot.timestamp, "%A, %B %e %Y", "GMT");

    std::cout << fmt.bold << fmt.cyan << fmt.underline << std::endl;
    std::cout << snapshot_time;
    std::cout << fmt.no_underline << profit_color << std::endl;

    printf("Current Equity:             $%'.2f (%+'.2f) (%+'.2f%%)\n",
           current_equity, current_profit, current_profit_percent);
    printf("Max Equity:                 $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           max_equity, max_profit, max_profit_percent,
           ::utils::time_::date_string(max_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Min Equity:                 $%'.2f (%+'.2f) (%+'.2f%%) @ %s\n",
           min_equity, min_profit, min_profit_percent,
           ::utils::time_::date_string(min_equity_timestamp, "%H:%M %Z",
                                       "America/Chicago")
               .c_str());
    printf("Original Equity:            $%'.2f\n", original_equity);
  }
}

#endif
