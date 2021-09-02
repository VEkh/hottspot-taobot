#ifndef ETRADE__STOCK_BOT_is_outside_wedge
#define ETRADE__STOCK_BOT_is_outside_wedge

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats
#include "stock_bot.h"                      // ETrade, fmt, quote_t
#include <algorithm>                        // std::max, std::min
#include <iostream>                         // std::cout, std::endl
#include <math.h>                           // INFINITY
#include <stdio.h>                          // printf

bool ETrade::StockBot::is_outside_wedge() {
  const closed_positions_stats_t stats = build_closed_positions_stats();
  const double current_price = this->quotes.back().current_price;
  const double excess_ratio = 0.15;
  const int loss_streak = stats.loss_streaks.current;

  const int closed_positions_l = this->closed_positions.size();

  const int end_time =
      this->closed_positions.at(closed_positions_l - 1).close_timestamp;
  const int start_time =
      this->closed_positions.at(closed_positions_l - loss_streak)
          .close_timestamp;

  double low = INFINITY;
  double high = -INFINITY;

  for (int i = this->quotes.size() - 1; i >= 0; i--) {
    const quote_t quote = this->quotes.at(i);

    if (quote.timestamp < start_time) {
      break;
    }

    if (quote.timestamp > end_time) {
      continue;
    }

    high = std::max(high, quote.current_price);
    low = std::min(low, quote.current_price);
  }

  const double wedge_bound_delta = excess_ratio * (high - low);
  const double lower_bound = low - wedge_bound_delta;
  const double upper_bound = high + wedge_bound_delta;

  std::cout << fmt.bold << fmt.cyan << fmt.underline;
  printf("🏴 Wedge Info: \n");
  std::cout << fmt.reset << fmt.bold << fmt.cyan;
  printf("High: $%.2f • Low: $%.2f • Upper Bound: $%.2f • Lower Bound: $%.2f\n",
         high, low, upper_bound, lower_bound);
  std::cout << fmt.reset;

  return current_price >= upper_bound || current_price <= lower_bound;
}

#endif
