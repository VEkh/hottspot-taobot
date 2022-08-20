#ifndef ALPACA__TAO_BOT_open_and_persist_position
#define ALPACA__TAO_BOT_open_and_persist_position

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 */
#include "tao_bot.h"

#include "compute_quantity.cpp"     // compute_quantity
#include "get_account_balance.cpp"  // get_account_balance
#include "open_position.cpp"        // open_position
#include "opposite_direction.cpp"   // opposite_direction
#include "order_win_result.cpp"     // order_win_result
#include "should_open_position.cpp" // should_open_position
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // puts
#include <unistd.h>                 // usleep
#include <utility>                  // std::pair

void Alpaca::TaoBot::open_and_persist_position() {
  if (!should_open_position(this->open_order_ptr)) {
    return;
  }

  bool open_order_opened = false;

  bool (*is_long_position)(Alpaca::TaoBot *) =
      [](Alpaca::TaoBot *this_) -> bool {
    if (!this_->closed_positions.size()) {
      return ::utils::boolean::flip_coin();
    }

    const position_t last_position = this_->closed_positions.back();

    if (this_->order_win_result(last_position) == order_win_result_t::WIN) {
      return last_position.open_order.action == order_action_t::SELL;
    }

    return last_position.close_order.action == order_action_t::BUY;
  };

  while (!open_order_opened) {
    this->account_balance = get_account_balance(this->account_balance);

    const double quantity = compute_quantity(this->symbol);

    if (quantity <= 0) {
      std::cout << fmt.bold << fmt.yellow;
      puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
           "have insufficient margin buying power.");
      std::cout << fmt.reset << std::endl;

      return;
    }

    const order_action_t open_order_action =
        is_long_position(this) ? order_action_t::BUY : order_action_t::SELL;

    const order_action_t close_order_action =
        opposite_direction(open_order_action);

    std::pair<order_t, order_t> new_orders =
        open_position(this->api_client, close_order_action, open_order_action,
                      "open", quantity, this->symbol);

    open_order_opened = !new_orders.second.id.empty();

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
