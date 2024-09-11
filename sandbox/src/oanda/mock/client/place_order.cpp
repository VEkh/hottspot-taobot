#ifndef OANDA__MOCK__CLIENT_place_order
#define OANDA__MOCK__CLIENT_place_order

#include "client.h" // Oanda::Mock::Client, order_status_t, order_t

void Oanda::Mock::Client::place_order(const long int epoch, order_t *order) {
  order->id = epoch;
  order->status = order_status_t::ORDER_PENDING;
  order->timestamp = epoch;
  order->trade_id = epoch;
}

#endif
