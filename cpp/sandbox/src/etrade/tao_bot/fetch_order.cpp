#ifndef ETRADE__TAO_BOT_fetch_order
#define ETRADE__TAO_BOT_fetch_order

/*
 * ETrade::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "etrade/deps.cpp" // json
#include <iostream>        // std::cout, std::endl
#include <stdio.h>         // printf
#include <string>          // std::string

json ETrade::TaoBot::fetch_order(const order_t *order) {
  json empty_order;

  if (!order->id) {
    return empty_order;
  }

  std::string order_response = this->api_client.fetch_order(order->id);

  if (order_response.empty()) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Order %d was blank. It may not exist.\n", order->id);
    std::cout << fmt.reset;

    return empty_order;
  }

  return json::parse(order_response);
}

#endif
