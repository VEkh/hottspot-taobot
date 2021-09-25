#ifndef ETRADE__TAO_BOT_open_position
#define ETRADE__TAO_BOT_open_position

/*
 * ETrade::TaoBot
 * etrade_client
 * fmt
 * gear_t
 * order_action_t
 * order_type_t
 * order_t
 */
#include "tao_bot.h"

#include "compute_quantity.cpp"          // compute_quantity
#include "etrade/constants.cpp"          // ETrade::constants
#include "fetch_account_balance.cpp"     // fetch_account_balance
#include "lib/curl_client/curl_client.h" // CurlClient
#include "should_open_position.cpp"      // should_open_position
#include <iostream>                      // std::cout, std::endl
#include <stdio.h>                       // printf
#include <string>                        // std::string

void ETrade::TaoBot::open_position() {
  if (!should_open_position()) {
    return;
  }

  this->account_balance = fetch_account_balance();

  const double current_price = this->quotes.back().current_price;
  this->quantity = compute_quantity();

  order_t new_open_order;
  new_open_order.action =
      this->is_long_position ? order_action_t::BUY : order_action_t::SELL_SHORT;
  new_open_order.quantity = this->quantity;
  new_open_order.symbol = this->symbol;
  new_open_order.type = order_type_t::MARKET;

  order_t new_close_order;
  new_close_order.action = this->is_long_position
                               ? order_action_t::SELL
                               : order_action_t::BUY_TO_COVER;
  new_close_order.quantity = this->quantity;
  new_close_order.symbol = this->symbol;
  new_close_order.type = order_type_t::MARKET;

  this->close_order = new_close_order;
  this->close_order_ptr = &(this->close_order);
  this->open_order = new_open_order;
  this->open_order_ptr = &(this->open_order);

  const char *order_action =
      ETrade::constants::ORDER_ACTIONS[this->open_order.action];

  const char *log_icon = this->ICONS[order_action];

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << log_icon << " " << order_action << ": Placing open order."
            << std::endl;
  std::cout << fmt.reset;

  CurlClient curl_client = etrade_client.place_order(this->open_order_ptr);

  if (etrade_client.is_next_cycle_retry_error(curl_client)) {
    std::cout << fmt.bold << fmt.yellow;

    printf("%s %s: ", log_icon, order_action);

    switch (curl_client.response.error_code) {
    case 100: {
      puts("Account Key Error 🐞 (100). Retrying.");

      break;
    }

    case 3010: {
      puts("Insufficient Funds Error 😓 (3010).");
      printf("Attempted quantity: %i\n", this->quantity);

      break;
    }

    case 33: {
      puts("This securiity is not shortable at this time (33).");

      break;
    }
    }

    std::cout << fmt.reset << std::endl;

    this->close_order_ptr = nullptr;
    this->open_order_ptr = nullptr;

    return;
  }

  std::cout << fmt.bold << fmt.cyan;
  std::cout << log_icon << " " << order_action << ": Placed open order."
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
