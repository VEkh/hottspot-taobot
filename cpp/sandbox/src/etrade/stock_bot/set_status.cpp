#if !defined ETRADE__STOCK_BOT_set_status
#define ETRADE__STOCK_BOT_set_status

#include "etrade/deps.cpp"    // json
#include "etrade/utils.cpp"   // ETrade::utils
#include "get_order_json.cpp" // get_order_json
#include "stock_bot.h"        // ETrade::StockBot, order_status_t, order_t
#include <string>             // std::string

void ETrade::StockBot::set_status(order_t *order) {
  json order_json = get_order_json(order);

  if (order_json.empty()) {
    return;
  }

  std::string status = order_json["OrderDetail"][0]["status"];

  order->status = ETrade::utils::to_order_status_t(status);
}

#endif
