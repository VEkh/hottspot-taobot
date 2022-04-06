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

#include "compute_hedge_quantities.cpp" // compute_hedge_quantities
#include "fetch_account_balance.cpp"    // fetch_account_balance
#include "open_position.cpp"            // open_position
#include "should_open_position.cpp"     // should_open_position
#include <iostream>                     // std::cout, std::endl
#include <stdio.h>                      // puts
#include <unistd.h>                     // usleep
#include <utility>                      // std::pair

void Alpaca::TaoBot::open_hedged_position() {
  if (!should_open_position(this->open_order_ptr) &&
      !should_open_position(this->hedge_open_order_ptr)) {
    return;
  }

  this->account_balance = fetch_account_balance(this->api_client);

  const std::pair<double, double> hedge_quantities = compute_hedge_quantities();

  if (hedge_quantities.first <= 0 || hedge_quantities.second <= 0) {
    std::cout << fmt.bold << fmt.yellow;
    puts("Can't open an order with 0 quantity 🤐.\nThis may be because you "
         "have insufficient margin buying power.");
    std::cout << fmt.reset << std::endl;

    return;
  }

  bool open_order_opened = false;
  bool hedge_open_order_opened = false;

  while (!open_order_opened) {
    std::pair<order_t, order_t> new_orders = open_position(
        this->api_client, order_action_t::SELL, order_action_t::BUY, "open",
        hedge_quantities.first, this->symbol);

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

  while (!hedge_open_order_opened) {
    const hedge_info_t hedge_info = this->HEDGE_PAIRS[this->symbol];
    const order_action_t closing_action =
        hedge_info.action == order_action_t::BUY ? order_action_t::SELL
                                                 : order_action_t::BUY;

    std::pair<order_t, order_t> new_hedge_orders =
        open_position(this->api_client, closing_action, hedge_info.action,
                      "hedge open", hedge_quantities.second, hedge_info.symbol);

    hedge_open_order_opened = !new_hedge_orders.second.id.empty();

    if (!hedge_open_order_opened) {
      std::cout << fmt.bold << fmt.red;
      puts("❗ Failed to open hedge order. Retrying.\n");
      std::cout << fmt.reset << std::endl;

      usleep(0.5e6);

      continue;
    }

    this->hedge_close_order = new_hedge_orders.first;
    this->hedge_close_order_ptr = &this->hedge_close_order;
    this->hedge_open_order = new_hedge_orders.second;
    this->hedge_open_order_ptr = &this->hedge_open_order;
  }
}

#endif
