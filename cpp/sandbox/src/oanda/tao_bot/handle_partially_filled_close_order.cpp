#ifndef OANDA__TAO_BOT_handle_partially_filled_close_order
#define OANDA__TAO_BOT_handle_partially_filled_close_order

/*
 * Oanda::TaoBot
 * fmt
 * order_t
 * trade_status_t
 */
#include "tao_bot.h"

#include "deps.cpp"                                // json, nlohmann
#include "fetch_trade.cpp"                         // fetch_trade
#include "handle_partially_filled_close_order.cpp" // handle_partially_filled_close_order
#include "lib/formatted.cpp"                       // Formatted
#include "oanda/utils.cpp"                         // Oanda::utils
#include <iostream>                                // std::cout, std::endl
#include <string>                                  // std::stoi, std::string

void Oanda::TaoBot::handle_partially_filled_close_order(const order_t *order) {
  try {
    json trade_json = fetch_trade(order->trade_id);

    const std::string status = trade_json["state"];

    if (Oanda::utils::to_trade_status_t(status) ==
        trade_status_t::TRADE_CLOSED) {
      return;
    }

    const std::string current_units = trade_json["currentUnits"];

    order_t new_close_order;
    new_close_order.action = order->action;
    new_close_order.quantity = std::stoi(current_units);
    new_close_order.symbol = order->symbol;
    new_close_order.time_in_force = order->time_in_force;
    new_close_order.type = order->type;

    this->close_order = new_close_order;
    this->close_order_ptr = &(this->close_order);

    std::cout << fmt.bold << fmt.yellow;
    printf("🙄 Order %i partially filled. Placing another order to close the "
           "remaining %i units.\n",
           order->id, new_close_order.quantity);
    std::cout << fmt.reset << std::endl;

    this->api_client.place_order(this->close_order_ptr);
    this->close_order.quantity = order->quantity;
  } catch (nlohmann::detail::type_error &) {
    std::string error_message = Formatted::error_message(
        std::string("OANDA__TAO_BOT_handle_partially_filled_close_order error "
                    "when reading the trade."));

    std::cout << error_message << fmt.reset << std::endl;
    handle_partially_filled_close_order(order);
  }
}

#endif
