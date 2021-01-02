#if !defined ETRADE__STRADDLE_get_order_status
#define ETRADE__STRADDLE_get_order_status

#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted
#include "straddle.h"        // ETrade::Straddle, order_t, placed_orders
#include <algorithm>         // std::find_if
#include <iostream>          // std::cout, std::endl
#include <string>            // std::string

ETrade::Straddle::order_status_t string_to_enum(const std::string &in) {
  char const *const *statuses = ETrade::Straddle::ORDER_STATUSES;
  int length = sizeof(ETrade::Straddle::ORDER_STATUSES) /
               sizeof(*ETrade::Straddle::ORDER_STATUSES);

  for (int i = 0; i < length; i++) {
    if (statuses[i] == in) {
      return (ETrade::Straddle::order_status_t)i;
    }
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Status <" << in << "> was not present in ORDER_STATUSES."
            << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

ETrade::Straddle::order_status_t
ETrade::Straddle::get_order_status(const order_t &order) {
  if (!order.id) {
    return order_status_t::ORDER_PENDING;
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

  std::string status = (*order_iterator)["OrderDetail"][0]["status"];

  return string_to_enum(status);
}

#endif
