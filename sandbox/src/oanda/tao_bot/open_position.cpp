#ifndef OANDA__TAO_BOT_open_position
#define OANDA__TAO_BOT_open_position

/*
 * Oanda::TaoBot
 * fmt
 * order_action_t
 * order_time_in_force_t
 * order_type_t
 * order_t
 * reversal_type_t // TODO: Decide
 * stop_profit_type_t // TODO: Decide
 */
#include "tao_bot.h"

#include "lib/utils/string.cpp" // ::utils::string
#include "oanda/constants.cpp"  // Oanda::constants
#include <ctime>                // std::time
#include <iostream>             // std::cout, std::endl
#include <stdio.h>              // printf
#include <string>               // std::string
#include <utility>              // std::pair

// TODO: Decide
#include "current_mid.cpp"          // current_mid
#include "day_range_percentile.cpp" // day_range_percentile

std::pair<Oanda::TaoBot::order_t, Oanda::TaoBot::order_t>
Oanda::TaoBot::open_position(const order_action_t close_action,
                             const order_action_t open_action,
                             const char *order_description,
                             const int quantity) {
  order_t new_open_order;
  new_open_order.action = open_action;
  new_open_order.day_candle = this->day_candle; // TODO: Decide
  new_open_order.entry_reversal = this->entry_reversal;
  new_open_order.max_profit_at = this->current_epoch;
  new_open_order.min_profit_at = this->current_epoch;
  new_open_order.quantity = quantity;
  new_open_order.symbol = this->symbol;
  new_open_order.time_in_force = order_time_in_force_t::FOK;
  new_open_order.type = order_type_t::MARKET;

  if (this->api_client.config.should_stop_profit) {
    const reversal_type_t reversal_type = new_open_order.entry_reversal.type;

    const bool is_reversal_above_threshold =
        day_range_percentile(this->day_candle, current_mid()) >=
        this->EQUATOR_PERCENTILE;

    if (reversal_type == reversal_type_t::REVERSAL_LOW &&
        is_reversal_above_threshold) {
      new_open_order.stop_profit_type =
          stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE;
    } else if (reversal_type == reversal_type_t::REVERSAL_HIGH &&
               !is_reversal_above_threshold) {
      new_open_order.stop_profit_type =
          stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE;
    } else {
      new_open_order.stop_profit_type =
          stop_profit_type_t::STOP_PROFIT_CROSS_RANGE;
    }
  }

  order_t new_close_order;
  new_close_order.action = close_action;
  new_close_order.max_profit_at = this->current_epoch;
  new_close_order.min_profit_at = this->current_epoch;
  new_close_order.quantity = quantity;
  new_close_order.symbol = this->symbol;
  new_close_order.time_in_force = order_time_in_force_t::FOK;
  new_close_order.type = order_type_t::MARKET;

  const char *order_action =
      Oanda::constants::ORDER_ACTIONS[new_open_order.action];

  const char *order_icon = this->ICONS[order_action];
  const std::string order_action_label = ::utils::string::upcase(order_action);

  std::cout << fmt.bold << fmt.green << std::endl;
  printf("%s %s: Placing %s order.\n", order_icon, order_action_label.c_str(),
         order_description);
  std::cout << fmt.reset;

  if (this->backtest.is_active) {
    this->mock_api_client.place_order(this->current_epoch, &new_open_order);
  } else {
    this->api_client.place_order(&new_open_order);
  }

  if (new_open_order.status != order_status_t::ORDER_PENDING) {
    return {order_t(), order_t()};
  }

  std::cout << fmt.bold << fmt.cyan;
  printf("%s %s: Placed %s order.\n", order_icon, order_action_label.c_str(),
         order_description);
  std::cout << fmt.reset << std::endl;

  return {new_close_order, new_open_order};
}

#endif
