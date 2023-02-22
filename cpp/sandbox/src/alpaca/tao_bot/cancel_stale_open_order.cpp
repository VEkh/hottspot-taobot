#ifndef ALPACA__TAO_BOT_cancel_stale_open_order
#define ALPACA__TAO_BOT_cancel_stale_open_order

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "tao_bot.h"                // Alpaca::TaoBot, order_t, order_status_t
#include <ctime>                    // std::time, std::time_t
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf

void Alpaca::TaoBot::cancel_stale_open_order() {
  if (!this->open_order_ptr) {
    return;
  }

  if (this->open_order_ptr->status == order_status_t::ORDER_CANCELED) {
    this->open_order_ptr = nullptr;

    return;
  }

  if (!(this->open_order_ptr->status == order_status_t::ORDER_ACCEPTED ||
        this->open_order_ptr->status == order_status_t::ORDER_CANCELED ||
        this->open_order_ptr->status == order_status_t::ORDER_NEW)) {
    return;
  }

  const std::time_t now = std::time(nullptr);
  const int time_limit_seconds = 2 * 60;

  const bool is_order_stale =
      (now - this->open_order_ptr->timestamp) >= time_limit_seconds;

  if (!is_order_stale) {
    return;
  }

  std::cout << fmt.yellow << fmt.bold;
  printf("😴 Clearing stale open order %s.\n", this->open_order_ptr->id.c_str());
  std::cout << fmt.reset;

  const std::string cancel_response =
      this->api_client.cancel_order(this->open_order_ptr);

  std::cout << fmt.red << fmt.bold;
  printf("Cancel Response: %s\n", cancel_response.c_str());
  std::cout << fmt.reset;

  if (!cancel_response.empty()) {
    json response_json = ::utils::json::parse_with_catch(
        cancel_response, "ALPACA__CLIENT_cancel_order");

    std::cout << fmt.red << fmt.bold;
    printf("❌ Failed to cancel order %s: %s\n",
           this->open_order_ptr->id.c_str(), response_json.dump(2).c_str());
    std::cout << fmt.reset;

    return;
  }

  std::cout << fmt.green << fmt.bold;
  printf("✅ Successfully canceled order %s\n",
         this->open_order_ptr->id.c_str());
  std::cout << fmt.reset << std::endl;
}

#endif
