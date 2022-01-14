#ifndef ALPACA__TAO_BOT_capture_profit
#define ALPACA__TAO_BOT_capture_profit

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_status_t
 * position_t
 */
#include "tao_bot.h"

#include "loss_to_recover.cpp" // loss_to_recover
#include "position_profit.cpp" // position_profit
#include <algorithm>           // std::min
#include <ctime>               // std::time
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // puts

void Alpaca::TaoBot::capture_profit(const position_t &position) {
  if (!this->is_capturing_profit) {
    return;
  }

  std::cout << fmt.bold << fmt.yellow;
  puts("🤲🏾 Capturing profit");
  std::cout << fmt.reset << std::endl;

  const double trimmed_deficit =
      std::min((loss_to_recover() + position_profit(position)), 1.0e-6);

  order_t capture_profit_order;
  capture_profit_order.action = order_action_t::SELL;
  capture_profit_order.profit = trimmed_deficit;
  capture_profit_order.quantity = 1;
  capture_profit_order.status = order_status_t::ORDER_FILLED;
  capture_profit_order.symbol = this->symbol;

  position_t capture_profit_position = {
      .close_order = capture_profit_order,
      .close_timestamp = (int)std::time(nullptr),
      .open_order = capture_profit_order,
  };

  this->closed_positions.push_back(capture_profit_position);
  this->is_capturing_profit = false;
}

#endif
