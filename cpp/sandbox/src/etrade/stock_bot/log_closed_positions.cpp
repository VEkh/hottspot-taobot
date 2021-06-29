#ifndef ETRADE__STOCK_BOT_log_closed_positions
#define ETRADE__STOCK_BOT_log_closed_positions

/*
 * ETrade::StockBot
 * fmt
 * position_result_t
 */
#include "stock_bot.h"

#include "build_closed_positions_results.cpp" // build_closed_positions_results
#include <map>                                // std::map

void ETrade::StockBot::log_closed_positions() {
  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  std::cout << "📕 Closed Positions" << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;

  std::map<position_result_t, int> closed_positions_results =
      build_closed_positions_results();

  int win_count = closed_positions_results[position_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  std::cout << "Wins: " << win_count;
  std::cout << " • Losses: "
            << closed_positions_results[position_result_t::LOSS];
  std::cout << " • Ties: " << closed_positions_results[position_result_t::TIE];
  std::cout << " • Total: " << total_count;
  std::cout << std::endl;

  std::cout << "Win %: " << win_percentage << std::endl;

  std::cout << fmt.reset << std::endl;
}

#endif
