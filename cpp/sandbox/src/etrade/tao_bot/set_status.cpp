#ifndef ETRADE__TAO_BOT_set_status
#define ETRADE__TAO_BOT_set_status

#include "etrade/deps.cpp"  // json
#include "etrade/utils.cpp" // ETrade::utils
#include "fetch_order.cpp"  // fetch_order
#include "tao_bot.h"      // ETrade::TaoBot, order_status_t, order_t
#include <string>           // std::string

void ETrade::TaoBot::set_status(order_t *order) {
  json order_json = fetch_order(order);

  if (order_json.empty()) {
    return;
  }

  std::string status = order_json["OrderDetail"][0]["status"];

  order->status = ETrade::utils::to_order_status_t(status);
}

#endif
