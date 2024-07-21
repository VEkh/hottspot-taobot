#ifndef ALPACA__TAO_BOT_fetch_order
#define ALPACA__TAO_BOT_fetch_order

/*
 * Alpaca::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "deps.cpp"                 // json
#include "lib/utils/json.cpp"       // ::utils::json
#include <iostream>                 // std::cout, std::endl
#include <stdio.h>                  // printf
#include <string>                   // std::string

json Alpaca::TaoBot::fetch_order(const order_t *order) {
  json empty_order;

  if (order->id.empty()) {
    return empty_order;
  }

  const std::string order_response =
      this->backtest.is_active
          ? this->backtest.fetch_order(order, this->current_quote)
          : this->api_client.fetch_order(order->id);

  return ::utils::json::parse_with_catch(order_response,
                                         "ALPACA__TAO_BOT_fetch_order");
}

#endif
