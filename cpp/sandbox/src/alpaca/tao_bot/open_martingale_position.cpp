#ifndef ALPACA__TAO_BOT_open_martingale_position
#define ALPACA__TAO_BOT_open_martingale_position

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 */
#include "tao_bot.h"

#include "alpaca/constants.cpp"            // Alpaca::constants
#include "build_performance.cpp"           // build_performance
#include "compute_martingale_quantity.cpp" // compute_martingale_quantity
#include "fetch_account_balance.cpp"       // fetch_account_balance
#include "lib/utils/string.cpp"            // ::utils::string
#include "should_open_position.cpp"        // should_open_position
#include "write_performance.cpp"           // write_performance
#include <iostream>                        // std::cout, std::endl
#include <math.h>                          // ceil
#include <stdio.h>                         // printf

void Alpaca::TaoBot::open_martingale_position() {
  if (!should_open_position(this->open_order_ptr)) {
    return;
  }

  this->account_balance = fetch_account_balance(this->api_client);

  const double quantity_ = compute_martingale_quantity();

  if (quantity_ <= 0) {
    std::cout << fmt.bold << fmt.yellow;
    puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
         "have insufficient margin buying power.");
    std::cout << fmt.reset;

    return;
  }

  this->quantity = this->is_long_position ? quantity_ : ceil(quantity_);

  order_t new_open_order;
  new_open_order.action =
      this->is_long_position ? order_action_t::BUY : order_action_t::SELL;
  new_open_order.quantity = this->quantity;
  new_open_order.symbol = this->symbol;
  new_open_order.type = order_type_t::MARKET;

  order_t new_close_order;
  new_close_order.action =
      this->is_long_position ? order_action_t::SELL : order_action_t::BUY;
  new_close_order.quantity = this->quantity;
  new_close_order.symbol = this->symbol;
  new_close_order.type = order_type_t::MARKET;

  this->close_order = new_close_order;
  this->close_order_ptr = &(this->close_order);
  this->open_order = new_open_order;
  this->open_order_ptr = &(this->open_order);

  const char *order_action =
      Alpaca::constants::ORDER_ACTIONS[this->open_order.action];

  std::string order_action_label = ::utils::string::upcase(order_action);

  const char *log_icon = this->ICONS[order_action];

  std::cout << fmt.bold << fmt.green << std::endl;
  printf("%s %s: Placing open order.\n", log_icon, order_action_label.c_str());
  std::cout << fmt.reset;

  this->api_client.place_order(this->open_order_ptr);

  if (this->open_order.status != order_status_t::ORDER_NEW) {
    std::cout << fmt.bold << fmt.red;
    puts("❗ Failed to open order. Retrying.\n");
    std::cout << fmt.reset << std::endl;

    this->close_order_ptr = nullptr;
    this->open_order_ptr = nullptr;

    this->performance = build_performance();
    write_performance();

    return;
  }

  std::cout << fmt.bold << fmt.cyan;
  printf("%s %s: Placed open order.\n", log_icon, order_action_label.c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
