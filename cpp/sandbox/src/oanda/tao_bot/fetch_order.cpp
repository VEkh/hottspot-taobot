#ifndef OANDA__TAO_BOT_fetch_order
#define OANDA__TAO_BOT_fetch_order

/*
 * Oanda::TaoBot
 * order_t
 */
#include "tao_bot.h"

#include "deps.cpp"           // json
#include "lib/utils/json.cpp" // ::utils::json
#include <string>             // std::string

json Oanda::TaoBot::fetch_order(const order_t *order) {
  json empty_order;

  if (!order->id) {
    return empty_order;
  }

  std::string response = this->api_client.fetch_order(order->id);

  return ::utils::json::parse_with_catch(response,
                                         "OANDA__TAO_BOT_fetch_order");
}

#endif
