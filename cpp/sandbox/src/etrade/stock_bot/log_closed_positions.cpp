#ifndef ETRADE__STOCK_BOT_log_closed_positions
#define ETRADE__STOCK_BOT_log_closed_positions

/*
 * ETrade::StockBot
 * closed_positions_stats_t
 * fmt
 * order_win_result_t
 * position_t
 */
#include "stock_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include <iostream>                         // std::cout, std::endl
#include <map>                              // std::map
#include <stdio.h>                          // printf

void ETrade::StockBot::log_closed_positions() {
  closed_positions_stats_t stats = build_closed_positions_stats();
  std::map<order_win_result_t, int> closed_positions_results = stats.results;

  int win_count = closed_positions_results[order_win_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  std::cout << "📕 Closed Positions" << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.yellow << fmt.bold;
  std::cout << "Profits: [";

  for (int i = 0, l = this->closed_positions.size(); i < l; i++) {
    const position_t position = this->closed_positions[i];

    if (i != 0) {
      printf(", ");
    }

    printf("%+.2f:%d", position.close_order.profit,
           position.close_order.quantity);
  }

  std::cout << "]" << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;

  printf("Wins: %d (%.2f%%) • Losses: %d • Total: %d\n", win_count,
         win_percentage, closed_positions_results[order_win_result_t::LOSS],
         total_count);

  printf("Loss Streak => Current: %d • Longest: %d\n", stats.loss_streak,
         stats.longest_loss_streak);

  printf("Win Streak  => Current: %d • Longest: %d\n", stats.win_streak,
         stats.longest_win_streak);

  printf("Total Profit: %+'.2f\n", stats.total_profit);

  std::cout << fmt.reset << std::endl;
}

#endif
