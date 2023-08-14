#ifndef ALPACA__TAO_BOT_log_performance
#define ALPACA__TAO_BOT_log_performance

/*
 * Alpaca::TaoBot
 * fmt
 * order_win_result_t
 * performance_t
 * position_t
 */
#include "tao_bot.h"

#include "closed_position_profit.cpp" // closed_position_profit
#include "lib/utils/integer.cpp"      // utils::integer_
#include <algorithm>                  // std::max
#include <iostream>                   // std::cout, std::endl
#include <map>                        // std::map
#include <math.h>                     // abs
#include <stdio.h>                    // printf, puts

void Alpaca::TaoBot::log_performance() {
  performance_t stats = this->performance;
  std::map<order_win_result_t, int> closed_positions_results = stats.results;

  int win_count = closed_positions_results[order_win_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  void (*print_counts)(std::map<int, int> &
                       counts) = [](std::map<int, int> &counts) -> void {
    std::map<int, int>::iterator it;

    printf("Counts: {");

    for (it = counts.begin(); it != counts.end(); it++) {
      if (it != counts.begin()) {
        printf(", ");
      }

      printf("%d: %d", it->first, it->second);
    }

    printf("}");
  };

  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  puts("📕 Closed Positions");
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;
  printf("Wins: %d (%.2f%%) • Losses: %d • Total: %d\n", win_count,
         win_percentage, closed_positions_results[order_win_result_t::LOSS],
         total_count);

  printf("Loss Streak => Current: %d • Longest: %d • ",
         stats.loss_streaks.current, stats.loss_streaks.longest);
  print_counts(stats.loss_streaks.counts);
  puts("");

  printf("Win  Streak => Current: %d • Longest: %d • ",
         stats.win_streaks.current, stats.win_streaks.longest);
  print_counts(stats.win_streaks.counts);
  puts("\n");

  printf("Current Balance: %+'.2f • Max Balance: %+'.2f\n",
         stats.current_balance, stats.max_balance);

  printf("Current Loss Streak Deficit: %+'.2f • Total Deficit: %+'.2f\n\n",
         stats.current_loss_streak_balance,
         stats.current_balance - stats.max_balance);

  printf("Profits (Last 20): [");

  const int l = this->closed_positions.size();
  const int start_index = std::max(l - 20, 0);

  for (int i = start_index; i < l; i++) {
    const position_t position = this->closed_positions[i];

    if (i != start_index) {
      printf(", ");
    }

    const double profit = closed_position_profit(position);

    printf("%+.2f", profit);
  }

  puts("]");

  double total_cash_moved = 0;

  for (int i = 0; i < l; i++) {
    const position_t position = this->closed_positions[i];

    total_cash_moved += abs(closed_position_profit(position));
  }

  printf("Total Cash Moved: %+'.2f\n", total_cash_moved);

  std::cout << fmt.reset << std::endl;
}

#endif
