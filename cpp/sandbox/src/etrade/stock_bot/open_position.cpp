#if !defined ETRADE__STOCK_BOT_open_position
#define ETRADE__STOCK_BOT_open_position

/*
 * ETrade::StockBot
 * etrade_client
 * fmt
 * order_action_t
 * order_status_t
 * order_type_t
 */
#include "stock_bot.h"

#include "should_open_position.cpp" // should_open_position

void ETrade::StockBot::open_position() {
  if (!should_open_position()) {
    return;
  }

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
