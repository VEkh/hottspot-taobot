#ifndef OANDA__TAO_BOT_set_status
#define OANDA__TAO_BOT_set_status

/*
 * Oanda::TaoBot
 * fmt
 * order_status_t
 * order_t
 */
#include "tao_bot.h"

#include "build_performance.cpp" // build_performance
#include "deps.cpp"              // json, nlohmann
#include "fetch_order.cpp"       // fetch_order
#include "oanda/constants.cpp"   // Oanda::constants
#include "oanda/utils.cpp"       // Oanda::utils
#include "write_performance.cpp" // write_performance
#include <iostream>              // std::cout, std::endl
#include <stdio.h>               // printf
#include <string>                // std::string

void Oanda::TaoBot::set_status(order_t *order) {
  const order_status_t original_status = order->status;

  if (original_status == order_status_t::ORDER_FILLED) {
    return;
  }

  json order_json = fetch_order(order);

  if (original_status == order_status_t::ORDER_PENDING) {
    std::cout << fmt.bold << fmt.yellow;
    printf("[OANDA__TAO_BOT_set_status]: PENDING order response: %s\n",
           order_json.dump(2).c_str());
    std::cout << fmt.reset << std::endl;
  }

  if (order_json.empty()) {
    return;
  }

  std::string status;

  try {
    status = order_json["state"];
  } catch (nlohmann::detail::type_error &) {
    return set_status(order);
  }

  order->status = Oanda::utils::to_order_status_t(status);

  if (original_status != order_status_t::ORDER_FILLED &&
      order->status == order_status_t::ORDER_FILLED) {
    const char *order_action = Oanda::constants::ORDER_ACTIONS[order->action];
    const char *log_icon = this->ICONS[order_action];

    std::cout << fmt.bold << fmt.green << std::endl;
    printf("%s Executed %s order.\n", log_icon, order_action);
    std::cout << fmt.reset;

    this->performance = build_performance();
    write_performance();
  }
}

#endif
