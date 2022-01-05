#ifndef ALPACA__TAO_BOT_set_execution_price
#define ALPACA__TAO_BOT_set_execution_price

/*
 * Alpaca::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "deps.cpp"        // json
#include "fetch_order.cpp" // fetch_order
#include <iostream>        // std::cout, std::endl
#include <stdio.h>         // printf
#include <string>          // std::stod
#include <unistd.h>        // usleep

void Alpaca::TaoBot::set_execution_price(order_t *order) {
  if (order->execution_price) {
    return;
  }

  json order_json = fetch_order(order);

  if (order_json.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Order %s was empty. Trying again\n", order->id.c_str());
    std::cout << fmt.reset;

    usleep(0.5 * 1e6);
    set_execution_price(order);
  }

  const std::string execution_price_string = order_json["filled_avg_price"];

  order->execution_price = std::stod(execution_price_string);
}

#endif
