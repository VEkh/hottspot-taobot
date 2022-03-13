#ifndef ALPACA__TAO_BOT_set_execution_price
#define ALPACA__TAO_BOT_set_execution_price

/*
 * Alpaca::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "deps.cpp"                 // json
#include "fetch_order.cpp"          // fetch_order
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf
#include <string>                   // std::stod
#include <unistd.h>                 // usleep

void Alpaca::TaoBot::set_execution_price(order_t *order,
                                         Alpaca::Client &api_client_ref) {
  if (order->execution_price) {
    return;
  }

  if (order->id.empty()) {
    return;
  }

  json order_json = fetch_order(order, api_client_ref);

  if (!order_json.contains("filled_avg_price")) {
    return set_execution_price(order, api_client_ref);
  }

  const std::string execution_price_string = order_json["filled_avg_price"];

  order->execution_price = (double)std::stod(execution_price_string);
}

#endif
