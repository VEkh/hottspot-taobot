#if !defined ETRADE__STRADDLE_set_status
#define ETRADE__STRADDLE_set_status

#include "etrade/deps.cpp"    // json
#include "get_order_json.cpp" // get_order_json
#include "lib/formatted.cpp"  // Formatted
#include "straddle.h"         // ETrade::Straddle, order_t
#include <iostream>           // std::cout, std::endl
#include <string>             // std::string

ETrade::Straddle::order_status_t string_to_enum(const std::string &in) {
  int length = sizeof(ETrade::Straddle::ORDER_STATUSES) /
               sizeof(*ETrade::Straddle::ORDER_STATUSES);

  for (int i = 0; i < length; i++) {
    if (ETrade::Straddle::ORDER_STATUSES[i] == in) {
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

void ETrade::Straddle::set_status(order_t &order) {
  json order_json = get_order_json(order);

  if (order_json.empty()) {
    return;
  }

  std::string status = order_json["OrderDetail"][0]["status"];

  order.status = string_to_enum(status);
}

#endif