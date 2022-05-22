#ifndef ALPACA__TAO_BOT_set_status
#define ALPACA__TAO_BOT_set_status

/*
 * Alpaca::TaoBot
 * fmt
 * order_status_t
 * order_t
 */
#include "tao_bot.h"

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "alpaca/constants.cpp"     // Alpaca::constants
#include "alpaca/utils.cpp"         // Alpaca::utils
#include "deps.cpp"                 // json
#include "fetch_order.cpp"          // fetch_order
#include "lib/utils/string.cpp"     // ::utils::string
#include <ctime>                    // std::time
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf
#include <string>                   // std::string

void Alpaca::TaoBot::set_status(Alpaca::Client &api_client_ref,
                                order_t *order) {
  if (!order) {
    return;
  }

  const order_status_t original_status = order->status;

  if (original_status == order_status_t::ORDER_FILLED) {
    return;
  }

  json order_json = fetch_order(api_client_ref, order);

  if (order_json.empty()) {
    return;
  }

  if (!order_json.contains("status")) {
    return set_status(api_client_ref, order);
  }

  const std::string status = order_json["status"];
  order->status = Alpaca::utils::to_order_status_t(status);

  if (original_status != order_status_t::ORDER_FILLED &&
      order->status == order_status_t::ORDER_FILLED) {
    order->runtime = (int)(std::time(nullptr) - this->started_at);
    order->timestamp = (int)std::time(nullptr);

    const char *order_action = Alpaca::constants::ORDER_ACTIONS[order->action];
    const char *log_icon = this->ICONS[order_action];

    std::cout << fmt.bold << fmt.green << std::endl;
    printf("%s Executed %s order.\n", log_icon,
           ::utils::string::upcase(order_action).c_str());
    std::cout << fmt.reset;
  }
}

#endif
