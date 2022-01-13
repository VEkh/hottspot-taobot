#ifndef ALPACA__TAO_BOT_capture_profit
#define ALPACA__TAO_BOT_capture_profit

/*
 * Alpaca::TaoBot
 * fmt
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
      std::min(loss_to_recover() + position_profit(position), 0.00);

  order_t trim_loss_order;
  trim_loss_order.profit = trimmed_deficit;
  trim_loss_order.quantity = 1;
  trim_loss_order.status = order_status_t::ORDER_FILLED;
  trim_loss_order.symbol = this->symbol;

  position_t loss_cut_position = {
      .close_order = trim_loss_order,
      .close_timestamp = (int)std::time(nullptr),
      .open_order = trim_loss_order,
  };

  this->closed_positions.push_back(loss_cut_position);
  this->is_capturing_profit = false;
}

#endif
