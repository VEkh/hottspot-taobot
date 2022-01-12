#ifndef ALPACA__TAO_BOT_trim_deficit
#define ALPACA__TAO_BOT_trim_deficit

/*
 * Alpaca::TaoBot
 * fmt
 * position_t
 */
#include "tao_bot.h"

#include "loss_to_recover.cpp" // loss_to_recover
#include "position_profit.cpp" // position_profit
#include <ctime>               // std::time
#include <iostream>            // std::cout, std::endl
#include <stdio.h>             // puts

void Alpaca::TaoBot::trim_deficit(const position_t &position) {
  if (!this->is_trimming_deficit) {
    return;
  }

  std::cout << fmt.bold << fmt.yellow;
  puts("🔪 Trimming losses");
  std::cout << fmt.reset << std::endl;

  const double trimmed_deficit = loss_to_recover() + position_profit(position);

  order_t trim_loss_order;
  trim_loss_order.profit = trimmed_deficit;
  trim_loss_order.quantity = 1;
  trim_loss_order.status = order_status_t::ORDER_FILLED;
  trim_loss_order.symbol = this->symbol;

  position_t loss_cut_position = {
      .close_order = trim_loss_order,
      .close_timestamp = (int)std::time(nullptr),
  };

  this->is_trimming_deficit = false;
}

#endif
