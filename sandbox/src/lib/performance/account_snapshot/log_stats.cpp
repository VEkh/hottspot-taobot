#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_log_stats
#define PERFORMANCE__ACCOUNT_SNAPSHOT_log_stats

#include "account_snapshot.h"  // Performance::AccountSnapshot, fmt
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // ::utils::float_
#include <iostream>            // std::cout, std::endl
#include <math.h>              // abs
#include <stdio.h>             // printf

void Performance::AccountSnapshot::log_stats() {
  std::cout << fmt.bold << fmt.cyan << fmt.underline << std ::endl;
  std::cout << "📊 Stats\n";
  std::cout << fmt.reset;

  const double avg_daily_dollars =
      this->stats.daily_dollars / this->stats.day_count;
  const double avg_daily_ratio =
      this->stats.daily_ratio / this->stats.day_count;
  const double win_rate_percent =
      100 * ((double)this->stats.win_count / this->stats.day_count);

  Formatted::Stream avg_daily_dollars_color =
      avg_daily_dollars < 0 ? fmt.red : fmt.green;
  Formatted::Stream avg_daily_ratio_color =
      avg_daily_ratio < 0 ? fmt.red : fmt.green;
  Formatted::Stream total_color =
      this->stats.daily_dollars < 0 ? fmt.red : fmt.green;

  std::cout << fmt.bold << avg_daily_dollars_color;
  printf("Avg Daily Return:           %c$%'.2f\n",
         ::utils::float_::sign_char(avg_daily_dollars), abs(avg_daily_dollars));

  std::cout << fmt.bold << avg_daily_ratio_color;
  printf("Avg Daily %% Return:         %+'.2f%%\n", avg_daily_ratio * 100.0);

  std::cout << fmt.bold << total_color;
  printf("Total Return:               %c$%'.2f\n",
         ::utils::float_::sign_char(this->stats.daily_dollars),
         abs(this->stats.daily_dollars));

  printf("Win Rate:                   %'iW (%.2f%%) %'iL (Total: %'i)\n",
         this->stats.win_count, win_rate_percent, this->stats.loss_count,
         this->stats.day_count);

  std::cout << std::endl;
}

#endif
