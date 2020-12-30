#if !defined ETRADE__STRADDLE_cancel_order
#define ETRADE__STRADDLE_cancel_order

#include "etrade/deps.cpp" // json
#include "straddle.h"      // ETrade::Straddle, etrade_client, order_t

CurlClient ETrade::Straddle::cancel_order(order_t &order) {
  CurlClient curl_client = etrade_client.cancel_order(order.id);

  json response = json::parse(curl_client.response.body);

  if (response.contains("CancelOrderResponse")) {
    order.status = order_status_t::ORDER_CANCELLED;
  }

  return curl_client;
}

#endif
