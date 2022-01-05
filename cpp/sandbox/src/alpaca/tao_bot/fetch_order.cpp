#ifndef ALPACA__TAO_BOT_fetch_order
#define ALPACA__TAO_BOT_fetch_order

/*
 * Alpaca::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include <iostream>           // std::cout, std::endl
#include <stdio.h>            // printf
#include <string>             // std::string

json Alpaca::TaoBot::fetch_order(const order_t *order) {
  json empty_order;

  if (order->id.empty()) {
    return empty_order;
  }

  std::string order_response = this->api_client.fetch_order(order->id);

  if (order_response.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Order %s was blank. It may not exist.\n", order->id.c_str());
    std::cout << fmt.reset;

    return empty_order;
  }

  return ::utils::json::parse_with_catch(order_response,
                                         "ALPACA__TAO_BOT_fetch_order");
}

#endif
