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
#include <cstdio>                           // printf
#include <iostream>                         // std::cout, std::endl
#include <map>                              // std::map

void ETrade::StockBot::log_closed_positions() {
  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  std::cout << "📕 Closed Positions" << std::endl;
  std::cout << fmt.reset;

  closed_positions_stats_t stats = build_closed_positions_stats();
  std::map<order_win_result_t, int> closed_positions_results = stats.results;

  int win_count = closed_positions_results[order_win_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  std::cout << fmt.bold << fmt.magenta;

  printf("Wins: %d • Losses: %d • Ties: %d • Total: %d\n", win_count,
         closed_positions_results[order_win_result_t::LOSS],
         closed_positions_results[order_win_result_t::TIE], total_count);

  printf("Win Streak: %d • Loss Streak: %d\n", stats.win_streak,
         stats.loss_streak);

  printf("Win %%: %.2f • Total Profit: $%.2f\n", win_percentage,
         stats.total_profit);

  std::cout << fmt.reset << std::endl;
}

#endif
