#ifndef PERFORMANCE__ACCOUNT_SNAPSHOT_log_stats
#define PERFORMANCE__ACCOUNT_SNAPSHOT_log_stats

#include "account_snapshot.h"  // Performance::AccountSnapshot, fmt
#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // ::utils::float_
#include "lib/utils/stats.cpp" // ::utils::stats
#include <iostream>            // std::cout, std::endl
#include <math.h>              // abs
#include <stdio.h>             // printf

void Performance::AccountSnapshot::log_stats() {
  std::cout << fmt.bold << fmt.cyan << fmt.underline << std ::endl;
  std::cout << "📊 Stats\n";
  std::cout << fmt.reset;

  const double avg_net_pl = this->stats.net_pl / this->stats.day_count;

  const double avg_daily_win_min_equity_percent =
      100.0 * ::utils::stats::mean(this->stats.daily_win_min_equity_ratios);

  const double std_daily_win_min_equity_percent =
      100.0 * ::utils::stats::std(this->stats.daily_win_min_equity_ratios);

  const double avg_daily_net_pl_ratio =
      this->stats.daily_net_pl_ratio / this->stats.day_count;

  const double total_net_pl_percent =
      100.0 * this->stats.net_pl / this->stats.original_snapshot.equity;

  const double win_rate_percent =
      100.0 * ((double)this->stats.win_count / this->stats.day_count);

  Formatted::Stream avg_net_pl_color = avg_net_pl < 0 ? fmt.red : fmt.green;

  Formatted::Stream avg_daily_net_pl_ratio_color =
      avg_daily_net_pl_ratio < 0 ? fmt.red : fmt.green;

  Formatted::Stream total_color = this->stats.net_pl < 0 ? fmt.red : fmt.green;

  std::cout << fmt.bold << avg_net_pl_color;
  printf("Avg Daily Return:           %c$%'.2f\n",
         ::utils::float_::sign_char(avg_net_pl), abs(avg_net_pl));

  std::cout << fmt.bold << avg_daily_net_pl_ratio_color;
  printf("Avg Daily %% Return:         %+'.2f%%\n",
         avg_daily_net_pl_ratio * 100.0);

  std::cout << fmt.bold << fmt.red;
  printf("Avg Win Min Equity %%:       %+'.2f%% (σ: %+'.4f%%)\n",
         avg_daily_win_min_equity_percent, std_daily_win_min_equity_percent);

  std::cout << fmt.bold << total_color;
  printf("Total Return:               %c$%'.2f (%.2f%%)\n",
         ::utils::float_::sign_char(this->stats.net_pl),
         abs(this->stats.net_pl), total_net_pl_percent);

  printf("Win Rate:                   %'iW (%.2f%%) %'iL (Total: %'i)\n",
         this->stats.win_count, win_rate_percent, this->stats.loss_count,
         this->stats.day_count);

  std::cout << std::endl;
}

#endif
