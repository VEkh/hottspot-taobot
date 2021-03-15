#if !defined ETRADE__STOCK_BOT_open_position
#define ETRADE__STOCK_BOT_open_position

/*
 * ETrade::StockBot
 * etrade_client
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 */
#include "stock_bot.h"

#include "etrade/constants.cpp"     // ETrade::constants
#include "should_open_position.cpp" // should_open_position
#include <iostream>                 // std::cout, std::endl

void ETrade::StockBot::open_position() {
  if (!should_open_position()) {
    return;
  }

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

  etrade_client.place_order(this->open_order_ptr);

  std::cout << fmt.bold << fmt.cyan;
  std::cout << log_icon << " " << order_action << ": Placed open order."
            << std::endl;
  std::cout << fmt.reset << std::endl;
}

#endif
