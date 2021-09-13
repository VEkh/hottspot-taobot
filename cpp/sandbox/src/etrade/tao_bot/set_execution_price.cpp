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

void ETrade::TaoBot::set_execution_price(order_t *order) {
  json order_json = fetch_order(order);

  if (order_json.empty() ||
      !order_json["OrderDetail"][0]["Instrument"][0].contains(
          "averageExecutionPrice")) {
    std::cout << fmt.bold << fmt.red;
    std::cout << "❌ Execution price not present in order: " << order_json.dump()
              << std::endl;
    std::cout << fmt.reset;
    return;
  }

  order->execution_price =
      order_json["OrderDetail"][0]["Instrument"][0]["averageExecutionPrice"];
}

#endif
