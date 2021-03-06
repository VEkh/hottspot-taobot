#if !defined ETRADE__STOCK_BOT_set_status
#define ETRADE__STOCK_BOT_set_status

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "get_order_json.cpp"     // get_order_json
#include "lib/formatted.cpp"      // Formatted
#include "stock_bot.h"            // ETrade::StockBot, order_status_t, order_t
#include <iostream>               // std::cout, std::endl
#include <string>                 // std::string

order_status_t string_to_enum(const std::string &in) {
  int length = sizeof(ETrade::Client::ORDER_STATUSES) /
               sizeof(*ETrade::Client::ORDER_STATUSES);

  for (int i = 0; i < length; i++) {
    if (ETrade::Client::ORDER_STATUSES[i] == in) {
      return (order_status_t)i;
    }
  }

  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.red;
  std::cout << "❌ Status <" << in << "> was not present in ORDER_STATUSES."
            << std::endl;
  std::cout << fmt.reset;

  exit(1);
}

void ETrade::StockBot::set_status(order_t *order) {
  json order_json = get_order_json(*order);

  if (order_json.empty()) {
    return;
  }

  std::string status = order_json["OrderDetail"][0]["status"];

  order->status = string_to_enum(status);
}

#endif
