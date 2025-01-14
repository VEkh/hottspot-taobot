#ifndef OANDA__TAO_BOT_set_execution_price
#define OANDA__TAO_BOT_set_execution_price

#include "deps.cpp"        // json, nlohmann
#include "fetch_trade.cpp" // fetch_trade
#include "tao_bot.h"       // Oanda::TaoBot, fmt, order_t
#include <iostream>        // std::cout, std::endl
#include <stdio.h>         // printf
#include <string>          // std::stod, std::string

void Oanda::TaoBot::set_execution_price(order_t *order) {
  if (order->execution_price) {
    return;
  }

  const json trade_json = fetch_trade(order);

  set_execution_price(order, trade_json);
}

void Oanda::TaoBot::set_execution_price(order_t *order, json trade_json) {
  if (order->execution_price) {
    return;
  }

  if (trade_json.empty() || !trade_json.contains("price")) {
    std::cout << fmt.bold << fmt.red;
    printf("❌ Execution price not present in trade: %s\n",
           trade_json.dump().c_str());
    std::cout << fmt.reset;

    return;
  }

  std::string price_string;

  try {
    price_string = trade_json["price"];

    if (trade_json.contains("averageClosePrice")) {
      price_string = trade_json["averageClosePrice"];
    }
  } catch (nlohmann::detail::type_error &) {
    return set_execution_price(order);
  }

  order->execution_price = (double)std::stod(price_string);
}

#endif
