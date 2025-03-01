#ifndef OANDA__TAO_BOT_set_status
#define OANDA__TAO_BOT_set_status

/*
 * Oanda::TaoBot
 * fmt
 * order_status_t
 * order_t
 */
#include "tao_bot.h"

#include "deps.cpp"                // json, nlohmann
#include "fetch_order.cpp"         // fetch_order
#include "fetch_trade.cpp"         // fetch_trade
#include "oanda/constants.cpp"     // Oanda::constants
#include "oanda/utils.cpp"         // Oanda::utils
#include "set_execution_price.cpp" // set_execution_price
#include <iostream>                // std::cout, std::endl
#include <math.h>                  // abs
#include <stdio.h>                 // printf
#include <string>                  // std::string, std::stol

void Oanda::TaoBot::set_status(order_t *order,
                               order_t *linked_order = nullptr) {
  const order_status_t original_status = order->status;
  std::string status;

  if (original_status == order_status_t::ORDER_FILLED) {
    return;
  }

  if (!order->trade_id && original_status != order_status_t::ORDER_INIT) {
    json order_json = fetch_order(order);

    std::cout << fmt.bold << fmt.yellow;
    printf("[OANDA__TAO_BOT_set_status]: Order %i has no `trade_id`\n",
           order->id);
    printf("[OANDA__TAO_BOT_set_status]: Fetched Order: %s\n",
           order_json.dump(2).c_str());
    std::cout << fmt.reset << std::endl;

    if (!order_json.empty()) {
      try {
        status = order_json["state"];
        order->status = Oanda::utils::to_order_status_t(status);
      } catch (nlohmann::detail::type_error &) {
        return;
      }
    }

    return;
  }

  json trade_json = fetch_trade(order);

  if (original_status == order_status_t::ORDER_PENDING) {
    std::cout << fmt.bold << fmt.yellow;
    printf("[OANDA__TAO_BOT_set_status]: PENDING order trade response: %s\n",
           trade_json.dump(2).c_str());
    std::cout << fmt.reset << std::endl;
  }

  if (trade_json.empty()) {
    return;
  }

  std::string trade_quantity_string;

  try {
    status = trade_json["state"];
    trade_quantity_string = trade_json["initialUnits"];
  } catch (nlohmann::detail::type_error &) {
    return set_status(order);
  }

  order->status = Oanda::utils::trade_status_to_order_status_t(status);

  if (original_status != order_status_t::ORDER_FILLED &&
      order->status == order_status_t::ORDER_FILLED) {
    const char *order_action = Oanda::constants::ORDER_ACTIONS[order->action];
    const char *log_icon = this->ICONS[order_action];
    const long int trade_quantity = abs(std::stol(trade_quantity_string));

    std::cout << fmt.bold << fmt.green << std::endl;
    printf("%s Executed %s order.\n", log_icon, order_action);
    std::cout << fmt.reset;

    if (trade_quantity != order->quantity) {
      std::cout << fmt.bold << fmt.red << std::endl;
      printf("🚨 Executed trade quantity (%li) doesn't match desired quantity "
             "(%li). Adjusting.\n",
             trade_quantity, order->quantity);
      std::cout << fmt.reset;

      order->quantity = trade_quantity;

      if (linked_order) {
        linked_order->quantity = trade_quantity;
      }

      exit(1);
    }

    set_execution_price(order, trade_json);
  }
}

#endif
