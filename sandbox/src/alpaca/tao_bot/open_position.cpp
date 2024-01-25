#ifndef ALPACA__TAO_BOT_open_position
#define ALPACA__TAO_BOT_open_position

/*
 * Alpaca::TaoBot
 * fmt
 * order_action_t
 * order_type_t
 * order_t
 * range_t // TODO: Decide
 */
#include "tao_bot.h"

#include "alpaca/constants.cpp" // Alpaca::constants
#include "lib/utils/string.cpp" // ::utils::string
#include <iostream>             // std::cout, std::endl
#include <stdio.h>              // printf
#include <string>               // std::string
#include <utility>              // std::pair

// TODO: Decide
#include "candles_range.cpp"     // candles_range
#include "is_reversing_loss.cpp" // is_reversing_loss

std::pair<Alpaca::TaoBot::order_t, Alpaca::TaoBot::order_t>
Alpaca::TaoBot::open_position(const order_action_t close_action,
                              const order_action_t open_action,
                              const char *order_description,
                              const double quantity_) {
  order_t new_open_order;
  new_open_order.action = open_action;
  new_open_order.max_profit_at = this->current_epoch;
  new_open_order.min_profit_at = this->current_epoch;
  new_open_order.quantity = quantity_;
  new_open_order.symbol = this->symbol;
  new_open_order.type = order_type_t::MARKET;

  // TODO: Decide
  if (this->api_client.config.should_await_consolidation_indicator) {
    if (is_reversing_loss()) {
      const position_t last_position = this->closed_positions.back();

      new_open_order.consolidation_range =
          last_position.open_order.consolidation_range;

      new_open_order.is_loss_reversal = last_position.close_order.profit < 0;
    } else {
      new_open_order.consolidation_range = this->active_consolidation;
    }
  }

  order_t new_close_order;
  new_close_order.action = close_action;
  new_close_order.max_profit_at = this->current_epoch;
  new_close_order.min_profit_at = this->current_epoch;
  new_close_order.quantity = quantity_;
  new_close_order.symbol = this->symbol;
  new_close_order.type = order_type_t::MARKET;

  const char *order_action =
      Alpaca::constants::ORDER_ACTIONS[new_open_order.action];

  const char *order_icon = this->ICONS[order_action];
  const std::string order_action_label = ::utils::string::upcase(order_action);

  std::cout << fmt.bold << fmt.green << std::endl;
  printf("%s %s: Placing %s order.\n", order_icon, order_action_label.c_str(),
         order_description);
  std::cout << fmt.reset;

  if (this->backtest.is_active) {
    this->backtest.place_order(this->current_epoch, &new_open_order);
  } else {
    this->api_client.place_order(&new_open_order);
  }

  if (!(new_open_order.status == order_status_t::ORDER_NEW ||
        new_open_order.status == order_status_t::ORDER_ACCEPTED)) {
    return {order_t(), order_t()};
  }

  std::cout << fmt.bold << fmt.cyan;
  printf("%s %s: Placed %s order.\n", order_icon, order_action_label.c_str(),
         order_description);
  std::cout << fmt.reset << std::endl;

  return {new_close_order, new_open_order};
}

#endif
