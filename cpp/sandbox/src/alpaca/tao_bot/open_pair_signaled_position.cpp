#ifndef ALPACA__TAO_BOT_open_pair_signaled_position
#define ALPACA__TAO_BOT_open_pair_signaled_position

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 */
#include "tao_bot.h"

#include "compute_quantity.cpp"         // current_price
#include "converted_signaler_price.cpp" // converted_signaler_price
#include "current_price.cpp"            // current_price
#include "fetch_account_balance.cpp"    // fetch_account_balance
#include "open_position.cpp"            // open_position
#include "opposite_direction.cpp"       // opposite_direction
#include "should_open_position.cpp"     // should_open_position
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // puts
#include <unistd.h>                     // usleep
#include <utility>                      // std::pair

void Alpaca::TaoBot::open_pair_signaled_position() {
  if (!should_open_position(this->open_order_ptr)) {
    return;
  }

  this->account_balance = fetch_account_balance(this->api_client);

  const std::string symbol_ = this->open_signal.signaled;
  const double quantity = compute_quantity(symbol_);

  if (quantity <= 0) {
    std::cout << fmt.bold << fmt.yellow;
    puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
         "have insufficient margin buying power.");
    std::cout << fmt.reset << std::endl;

    return;
  }

  bool open_order_opened = false;

  while (!open_order_opened) {
    const double converted_signaler_price_ =
        converted_signaler_price(this->open_signal);
    const double signaled_price = current_price(symbol_);

    const order_action_t open_order_action =
        this->open_signal.signaler_trend_direction;

    const order_action_t close_order_action =
        opposite_direction(open_order_action);

    std::pair<order_t, order_t> new_orders =
        open_position(this->api_client, close_order_action, open_order_action,
                      "open", quantity, symbol_);

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
