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
#include <map>                              // std::map

void ETrade::StockBot::log_closed_positions() {
  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  std::cout << "📕 Closed Positions" << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;

  closed_positions_stats_t stats = build_closed_positions_stats();
  std::map<order_win_result_t, int> closed_positions_results = stats.results;

  int win_count = closed_positions_results[order_win_result_t::WIN];
  int total_count = this->closed_positions.size();
  double win_percentage =
      !win_count ? 0 : (win_count / (double)total_count) * 100;

  std::cout << "Wins: " << win_count;
  std::cout << " • Losses: "
            << closed_positions_results[order_win_result_t::LOSS];
  std::cout << " • Ties: " << closed_positions_results[order_win_result_t::TIE];
  std::cout << " • Total: " << total_count;
  std::cout << std::endl;

  std::cout << "Win %: " << win_percentage << std::endl;

  double recalculated_total_profit = 0.00;

  std::cout << "Profits: [";
  for (int i = 0, l = this->closed_positions.size(); i < l; i++) {
    position_t position = this->closed_positions[i];

    if (i != 0) {
      std::cout << ", ";
    }

    recalculated_total_profit +=
        position.close_order.profit * position.close_order.quantity;

    std::cout << position.close_order.profit << ":"
              << position.close_order.quantity;
  }
  std::cout << "]" << std::endl;

  std::cout << "Total Profit: " << stats.total_profit << std::endl;
  std::cout << "Recalculated Total Profit: " << recalculated_total_profit
            << std::endl;

  std::cout << fmt.reset << std::endl;
}

#endif
