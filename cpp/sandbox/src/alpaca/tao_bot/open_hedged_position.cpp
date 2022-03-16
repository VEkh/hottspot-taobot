#ifndef ALPACA__TAO_BOT_open_hedged_position
#define ALPACA__TAO_BOT_open_hedged_position

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 */
#include "tao_bot.h"

#include "alpaca/constants.cpp"       // Alpaca::constants
#include "build_performance.cpp"      // build_performance
#include "compute_hedge_quantity.cpp" // compute_hedge_quantity
#include "current_price.cpp"          // current_price
#include "fetch_account_balance.cpp"  // fetch_account_balance
#include "lib/utils/string.cpp"       // ::utils::string
#include "should_open_position.cpp"   // should_open_position
#include "write_performance.cpp"      // write_performance
#include <iostream>                   // std::cout, std::endl
#include <math.h>                     // ceil
#include <stdio.h>                    // printf

void Alpaca::TaoBot::open_hedged_position() {
  if (!should_open_position()) {
    return;
  }

  this->account_balance = fetch_account_balance(this->api_client);
  this->hedge_account_balance = fetch_account_balance(this->hedge_api_client);

  const double quantity_ = compute_hedge_quantity();

  if (quantity_ <= 0) {
    std::cout << fmt.bold << fmt.yellow;
    puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
         "have insufficient margin buying power.");
    std::cout << fmt.reset;

    return;
  }

  this->quantity = quantity_;

  order_t new_open_order;
  new_open_order.action = order_action_t::BUY;
  new_open_order.quantity = this->quantity;
  new_open_order.symbol = this->symbol;
  new_open_order.type = order_type_t::MARKET;

  order_t new_close_order;
  new_close_order.action = order_action_t::SELL;
  new_close_order.quantity = this->quantity;
  new_close_order.symbol = this->symbol;
  new_close_order.type = order_type_t::MARKET;

  order_t new_hedge_open_order;
  new_hedge_open_order.action = order_action_t::SELL;
  new_hedge_open_order.quantity = this->quantity;
  new_hedge_open_order.symbol = this->symbol;
  new_hedge_open_order.type = order_type_t::MARKET;

  order_t new_hedge_close_order;
  new_hedge_close_order.action = order_action_t::BUY;
  new_hedge_close_order.quantity = this->quantity;
  new_hedge_close_order.symbol = this->symbol;
  new_hedge_close_order.type = order_type_t::MARKET;

  this->close_order = new_close_order;
  this->close_order_ptr = &this->close_order;
  this->open_order = new_open_order;
  this->open_order_ptr = &this->open_order;

  this->hedge_close_order = new_hedge_close_order;
  this->hedge_close_order_ptr = &this->hedge_close_order;
  this->hedge_open_order = new_hedge_open_order;
  this->hedge_open_order_ptr = &this->hedge_open_order;

  const char *hedge_order_action =
      Alpaca::constants::ORDER_ACTIONS[this->hedge_open_order.action];

  const char *hedge_order_icon = this->ICONS[hedge_order_action];

  const std::string hedge_order_action_label =
      ::utils::string::upcase(hedge_order_action);

  const char *order_action =
      Alpaca::constants::ORDER_ACTIONS[this->open_order.action];

  const char *order_icon = this->ICONS[order_action];
  const std::string order_action_label = ::utils::string::upcase(order_action);

  std::cout << fmt.bold << fmt.green << std::endl;
  printf("%s %s: Placing open order.\n", order_icon,
         order_action_label.c_str());
  std::cout << fmt.reset;

  this->api_client.place_order(this->open_order_ptr);

  std::cout << fmt.bold << fmt.green << std::endl;
  printf("%s %s: Placing hedge open order.\n", hedge_order_icon,
         hedge_order_action_label.c_str());
  std::cout << fmt.reset;

  this->hedge_api_client.place_order(this->hedge_open_order_ptr);

  if (this->open_order.status != order_status_t::ORDER_NEW ||
      this->hedge_open_order.status != order_status_t::ORDER_NEW) {
    std::cout << fmt.bold << fmt.red;
    puts("❗ Failed to open order. Retrying.\n");
    std::cout << fmt.reset << std::endl;

    this->close_order_ptr = nullptr;
    this->open_order_ptr = nullptr;

    this->hedge_close_order_ptr = nullptr;
    this->hedge_open_order_ptr = nullptr;

    this->performance = build_performance();
    write_performance();

    return;
  }

  std::cout << fmt.bold << fmt.cyan;
  printf("%s %s: Placed open order.\n", order_icon, order_action_label.c_str());
  std::cout << fmt.reset << std::endl;

  std::cout << fmt.bold << fmt.cyan;
  printf("%s %s: Placed hedge open order.\n", hedge_order_icon,
         hedge_order_action_label.c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
