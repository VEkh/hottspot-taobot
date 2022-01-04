#ifndef ALPACA__CLIENT_cancel_order
#define ALPACA__CLIENT_cancel_order

/*
 * Alpaca::Client
 * order_status_t
 * order_t
 */
#include "client.h"

#include "deps.cpp"                        // json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/json.cpp"              // ::utils::json
#include "post.cpp"                        // post
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

std::string Alpaca::Client::cancel_order(order_t *order) {
  std::string response_body = cancel_order(order->id);

  json response = ::utils::json::parse_with_catch(
      response_body, "ALPACA__CLIENT_cancel_order");

  order->status = order_status_t::ORDER_CANCELLED;

  return response_body;
}

std::string Alpaca::Client::cancel_order(const std::string &order_id) {
  if (order_id.empty()) {
    std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  std::string url = this->config.base_url + "/v2/orders/" + order_id;

  CurlClient curl_client = post({
      .body = "",
      .method = CurlClient::http_method_t::DELETE,
      .url = url,
  });

  return curl_client.response.body;
}

#endif
