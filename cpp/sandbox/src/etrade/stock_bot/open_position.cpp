#ifndef ETRADE__STOCK_BOT_open_position
#define ETRADE__STOCK_BOT_open_position

/*
 * ETrade::StockBot
 * etrade_client
 * fmt
 * gear_t
 * order_action_t
 * order_type_t
 * order_t
 */
#include "stock_bot.h"

#include "compute_normalized_quantity.cpp" // compute_normalized_quantity
#include "etrade/constants.cpp"            // ETrade::constants
#include "lib/curl_client/curl_client.h"   // CurlClient
#include "should_open_position.cpp"        // should_open_position
#include <iostream>                        // std::cout, std::endl
#include <stdio.h>                         // printf
#include <string>                          // std::string

void ETrade::StockBot::open_position() {
  if (!should_open_position()) {
    return;
  }

  const double current_price = this->quotes.back().current_price;
  this->quantity = compute_normalized_quantity();

  order_t new_open_order;
  new_open_order.action =
      this->is_long_position ? order_action_t::BUY : order_action_t::SELL_SHORT;
  new_open_order.limit_price = current_price;
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
      printf("Account Key Error 🐞 (100). Retrying.\n");

      break;
    }

    case 3010: {
      std::string message = "Insufficient Funds Error 😓 (3010).";

      if (this->FLAG_MARTINGALE) {
        this->martingale_quantity_multiplier *= 0.5;

        message += " Halving quantity.";
      }

      printf("%s\n", message.c_str());

      break;
    }

    case 33: {
      printf("This securiity is not shortable at this time (33).\n");

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
