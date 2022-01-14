#ifndef OANDA__TAO_BOT_complete_filled_order
#define OANDA__TAO_BOT_complete_filled_order

/*
 * Oanda::TaoBot
 * order_status_t
 */
#include "tao_bot.h"

#include "deps.cpp"                                // json
#include "fetch_order.cpp"                         // fetch_order
#include "handle_partially_filled_close_order.cpp" // handle_partially_filled_close_order
#include <string>                                  // std::stoi, std::string

void Oanda::TaoBot::complete_filled_order(order_t *order) {
  if (!order) {
    return;
  }

  if (order->status != order_status_t::ORDER_FILLED) {
    return;
  }

  if (order->trade_id) {
    return;
  }

  json order_json = fetch_order(order);

  std::string trade_id_string = "0";

  if (order_json.contains("tradeOpenedID")) {
    trade_id_string = order_json["tradeOpenedID"];
  } else if (order_json.contains("tradeReducedID")) {
    trade_id_string = order_json["tradeReducedID"];
    order->trade_id = std::stoi(trade_id_string);

    handle_partially_filled_close_order(order);

    return;
  } else if (order_json.contains("tradeClosedIDs")) {
    trade_id_string = order_json["tradeClosedIDs"][0];
  }

  order->trade_id = std::stoi(trade_id_string);
}

#endif
