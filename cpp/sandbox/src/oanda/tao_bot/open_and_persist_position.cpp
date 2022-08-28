#ifndef OANDA__TAO_BOT_open_and_persist_position
#define OANDA__TAO_BOT_open_and_persist_position

/*
 * Oanda::TaoBot
 * fmt
 * order_action_t
 * order_t
 */
#include "tao_bot.h"

#include "compute_quantity.cpp"      // compute_quantity
#include "get_account_balance.cpp"   // get_account_balance
#include "is_next_position_long.cpp" // is_next_position_long
#include "open_position.cpp"         // open_position
#include "opposite_direction.cpp"    // opposite_direction
#include "should_open_position.cpp"  // should_open_position
#include <iostream>                  // std::cout, std::endl
#include <stdio.h>                   // puts
#include <unistd.h>                  // usleep
#include <utility>                   // std::pair

void Oanda::TaoBot::open_and_persist_position() {
  if (!should_open_position()) {
    return;
  }

  puts("OANDA__TAO_BOT_open_position");
  std::cout << std::flush;

  bool open_order_opened = false;

  while (!open_order_opened) {
    this->account_balance = get_account_balance(this->account_balance);

    const int quantity = compute_quantity();

    if (quantity <= 0) {
      std::cout << fmt.bold << fmt.yellow;
      puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
           "have insufficient margin buying power.");
      std::cout << fmt.reset << std::endl;

      return;
    }

    const order_action_t open_order_action =
        is_next_position_long() ? order_action_t::BUY : order_action_t::SELL;

    const order_action_t close_order_action =
        opposite_direction(open_order_action);

    std::pair<order_t, order_t> new_orders =
        open_position(close_order_action, open_order_action, "open", quantity);

    open_order_opened = !new_orders.second.id;

    if (!open_order_opened) {
      std::cout << fmt.bold << fmt.red;
      puts("❗ Failed to open order. Retrying.\n");
      std::cout << fmt.reset << std::endl;

      usleep(0.5e6);

      continue;
    }

    this->close_order = new_orders.first;
    this->close_order_ptr = &this->close_order;
    this->open_order = new_orders.second;
    this->open_order_ptr = &this->open_order;
  }
}

#endif
