#ifndef OANDA__TAO_BOT_set_execution_price
#define OANDA__TAO_BOT_set_execution_price

/*
 * Oanda::TaoBot
 * fmt
 * order_t
 */
#include "tao_bot.h"

#include "deps.cpp" // json
#include <iostream> // std::cout, std::endl
#include <stdio.h>  // printf
#include <string>   // std::stod, std::string

void Oanda::TaoBot::set_execution_price(order_t *order) {
  if (order->execution_price) {
    return;
  }

  std::string trade_response = this->api_client.fetch_trade(order->trade_id);

  json trade_json = json::parse(trade_response);

  if (trade_json.empty() || !trade_json.contains("price")) {
    std::cout << fmt.bold << fmt.red;

    printf("❌ Execution price not present in trade: %s\n",
           trade_json.dump().c_str());

    std::cout << fmt.reset;

    return;
  }

  std::string price_string = trade_json["price"];
  order->execution_price = (double)std::stod(price_string);
}

#endif
