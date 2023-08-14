#ifndef ALPACA__CLIENT_cancel_order
#define ALPACA__CLIENT_cancel_order

/*
 * Alpaca::Client
 * order_status_t
 * order_t
 */
#include "client.h"

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "post.cpp"                        // post
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

std::string Alpaca::Client::cancel_order(const order_t *order) {
  return cancel_order(order->id);
}

std::string Alpaca::Client::cancel_order(const std::string &order_id) {
  if (order_id.empty()) {
    const std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  const std::string url = this->config.base_url + "/v2/orders/" + order_id;

  CurlClient curl_client = post({
      .body = "",
      .method = CurlClient::http_method_t::DELETE,
      .url = url,
  });

  return curl_client.response.body;
}

#endif
