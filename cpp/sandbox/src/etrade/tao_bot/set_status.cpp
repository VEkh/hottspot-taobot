#ifndef ETRADE__TAO_BOT_set_status
#define ETRADE__TAO_BOT_set_status

/*
 * ETrade::TaoBot
 * fmt
 * order_status_t
 * order_t
 */
#include "tao_bot.h"

#include "etrade/constants.cpp" // ETrade::constants
#include "etrade/deps.cpp"      // json
#include "etrade/utils.cpp"     // ETrade::utils
#include "fetch_order.cpp"      // fetch_order
#include <iostream>             // std::cout, std::endl
#include <stdio.h>              // printf
#include <string>               // std::string

void ETrade::TaoBot::set_status(order_t *order) {
  json order_json = fetch_order(order);

  if (order_json.empty()) {
    return;
  }

  order_status_t original_status = order->status;

  std::string status = order_json["OrderDetail"][0]["status"];
  order->status = ETrade::utils::to_order_status_t(status);

  if (original_status != order_status_t::ORDER_EXECUTED &&
      order->status == order_status_t::ORDER_EXECUTED) {
    const char *order_action = ETrade::constants::ORDER_ACTIONS[order->action];
    const char *log_icon = this->ICONS[order_action];

    std::cout << fmt.bold << fmt.green << std::endl;
    printf("%s Executed %s order.\n", log_icon, order_action);
    std::cout << fmt.reset;
  }
}

#endif
