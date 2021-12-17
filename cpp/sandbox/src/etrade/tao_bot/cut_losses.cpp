#ifndef ETRADE__TAO_BOT_cut_losses
#define ETRADE__TAO_BOT_cut_losses

/*
 * ETrade::TaoBot
 * fmt
 * order_status_t
 * position_t
 */
#include "tao_bot.h"

#include "build_performance.cpp" // build_performance
#include "math.h"                // abs
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf
#include <time.h>                // time, time_t

void ETrade::TaoBot::cut_losses() {
  const double threshold = 5e-3;
  const double percent_loss = this->performance.current_loss_streak_balance /
                              this->account_balance.balance;

  if (abs(percent_loss) < threshold) {
    return;
  }

  std::cout << fmt.bold << fmt.red;
  printf("🔪 <%s>'s losses are %'+.2f. Cutting losses 😭\n", this->symbol,
         this->performance.current_loss_streak_balance);
  std::cout << fmt.reset << std::endl;

  time_t now;
  time(&now);

  order_t loss_cut_order;
  loss_cut_order.profit = 1e-6;
  loss_cut_order.quantity = 1;
  loss_cut_order.status = order_status_t::ORDER_EXECUTED;
  loss_cut_order.symbol = this->symbol;

  position_t loss_cut_position = {
      .close_order = loss_cut_order,
      .close_timestamp = (int)now,
  };

  this->closed_positions.push_back(loss_cut_position);
  this->performance = build_performance();
}

#endif
