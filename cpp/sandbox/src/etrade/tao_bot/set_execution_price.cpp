#ifndef ETRADE__TAO_BOT_set_execution_price
#define ETRADE__TAO_BOT_set_execution_price

/*
 * ETrade::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "etrade/deps.cpp" // json
#include "fetch_order.cpp" // fetch_order
#include <iostream>        // std::cout, std::endl
#include <stdio.h>         // printf
#include <unistd.h>        // usleep

void ETrade::TaoBot::set_execution_price(order_t *order) {
  if (order->execution_price) {
    return;
  }

  json order_json = fetch_order(order);

  if (order_json.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Order %i was empty. Trying again\n", order->id);
    std::cout << fmt.reset;

    usleep(0.5 * 1e6);
    set_execution_price(order);
  }

  if (!order_json["OrderDetail"][0]["Instrument"][0].contains(
          "averageExecutionPrice")) {
    std::cout << fmt.bold << fmt.red;

    printf("❌ Execution price not present in order: %s\n",
           order_json.dump().c_str());

    std::cout << fmt.reset;

    return;
  }

  order->execution_price =
      order_json["OrderDetail"][0]["Instrument"][0]["averageExecutionPrice"];
}

#endif
