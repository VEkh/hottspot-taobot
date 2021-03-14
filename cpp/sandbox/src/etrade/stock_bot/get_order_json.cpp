#if !defined ETRADE__STOCK_BOT_get_order_json
#define ETRADE__STOCK_BOT_get_order_json

/*
 * ETrade::StockBot
 * order_t
 * placed_orders
 */
#include "stock_bot.h"

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include <algorithm>         // std::find_if
#include <iostream>          // std::cout, std::endl
#include <string>            // std::string

json ETrade::StockBot::get_order_json(const order_t *order) {
  json empty_order;

  if (!order->id) {
    return empty_order;
  }

  json::iterator order_iterator =
      std::find_if(this->placed_orders.begin(), this->placed_orders.end(),
                   [&order](json order_json) -> bool {
                     return order_json["orderId"] == order->id;
                   });

  if (order_iterator == this->placed_orders.end()) {
    std::cout << fmt.bold << fmt.red;
    std::cout << "❌ Order " << order->id
              << " was not present in your account's placed orders."
              << std::endl;
    std::cout << fmt.reset;

    return empty_order;
  }

  return *order_iterator;
}

#endif
