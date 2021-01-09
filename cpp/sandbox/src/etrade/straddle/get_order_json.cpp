#if !defined ETRADE__STRADDLE_get_order_json
#define ETRADE__STRADDLE_get_order_json

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "straddle.h"        // ETrade::Straddle, order_t, placed_orders
#include <algorithm>         // std::find_if
#include <iostream>          // std::cout, std::endl
#include <string>            // std::string

json ETrade::Straddle::get_order_json(const order_t &order) {
  if (!order.id) {
    json order_json;
    return order_json;
  }

  json::iterator order_iterator =
      std::find_if(placed_orders.begin(), placed_orders.end(),
                   [&order](json order_json) -> bool {
                     return order_json["orderId"] == order.id;
                   });

  if (order_iterator == placed_orders.end()) {
    Formatted::fmt_stream_t fmt = stream_format;

    std::cout << fmt.bold << fmt.red;
    std::cout << "❌ Order " << order.id
              << " was not present in your account's placed orders."
              << std::endl;
    std::cout << fmt.reset;

    exit(1);
  }

  return *order_iterator;
}

#endif
