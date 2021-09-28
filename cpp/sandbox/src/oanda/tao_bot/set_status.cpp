#ifndef OANDA__TAO_BOT_set_status
#define OANDA__TAO_BOT_set_status

#include "deps.cpp"        // json
#include "fetch_order.cpp" // fetch_order
#include "oanda/utils.cpp" // Oanda::utils
#include "tao_bot.h"       // Oanda::TaoBot, order_status_t, order_t
#include <string>          // std::string

void Oanda::TaoBot::set_status(order_t *order) {
  json order_json = fetch_order(order);

  if (order_json.empty()) {
    return;
  }

  std::string status = order_json["state"];

  order->status = Oanda::utils::to_order_status_t(status);
}

#endif
