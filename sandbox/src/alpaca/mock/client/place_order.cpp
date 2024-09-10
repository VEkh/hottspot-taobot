#ifndef ALPACA__MOCK__CLIENT_place_order
#define ALPACA__MOCK__CLIENT_place_order

#include "client.h" // Alpaca::Mock::Client, order_action_t, order_status_t, order_t
#include <stdio.h>  // snprintf
#include <string.h> // strlen
#include <string>   // std::to_string

void Alpaca::Mock::Client::place_order(const long int current_epoch,
                                       order_t *order) {
  const char *action = order->action == order_action_t::BUY ? "buy" : "sell";
  const char *id_format = "%s-%s-%li";

  const int id_l = strlen(id_format) + order->symbol.size() + strlen(action) +
                   std::to_string(current_epoch).size();

  char id[id_l];

  snprintf(id, id_l, id_format, order->symbol.c_str(), action, current_epoch);

  order->id = id;
  order->status = order_status_t::ORDER_NEW;
  order->timestamp = current_epoch;
}

#endif
