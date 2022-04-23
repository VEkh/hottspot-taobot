#ifndef ALPACA__TAO_BOT_cancel_stale_open_order
#define ALPACA__TAO_BOT_cancel_stale_open_order

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "tao_bot.h"                // Alpaca::TaoBot, order_t, order_status_t
#include <ctime>                    // std::time, std::time_t
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Alpaca::TaoBot::cancel_stale_open_order(Alpaca::Client &api_client_ref,
                                             const order_t *order_ptr) {
  if (!order_ptr) {
    return;
  }

  if (order_ptr->status == order_status_t::ORDER_CANCELED) {
    if (order_ptr == this->open_order_ptr) {
      this->open_order_ptr = nullptr;
    } else if (order_ptr == this->hedge_open_order_ptr) {
      this->hedge_open_order_ptr = nullptr;
    }

    return;
  }

  if (!(order_ptr->status == order_status_t::ORDER_ACCEPTED ||
        order_ptr->status == order_status_t::ORDER_CANCELED ||
        order_ptr->status == order_status_t::ORDER_NEW)) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  const int time_limit_seconds = 10;

  const bool is_order_stale =
      (now - order_ptr->timestamp) >= time_limit_seconds;

  if (!is_order_stale) {
    return;
  }

  std::cout << fmt.yellow << fmt.bold;
  printf("😴 Clearing stale open order %s.\n", order_ptr->id.c_str());
  std::cout << fmt.reset;

  const std::string cancel_response = api_client_ref.cancel_order(order_ptr);

  if (!cancel_response.empty()) {
    json response_json = ::utils::json::parse_with_catch(
        cancel_response, "ALPACA__CLIENT_cancel_order");

    std::cout << fmt.red << fmt.bold;
    printf("❌ Failed to cancel order %s: %s\n", order_ptr->id.c_str(),
           response_json.dump(2).c_str());
    std::cout << fmt.reset;

    return;
  }

  std::cout << fmt.green << fmt.bold;
  printf("✅ Successfully canceled order %s\n", order_ptr->id.c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
