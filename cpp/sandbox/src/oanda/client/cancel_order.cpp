#ifndef OANDA__CLIENT_cancel_order
#define OANDA__CLIENT_cancel_order

/*
 * Oanda::Client
 * order_status_t
 * order_t
 */
#include "client.h"

#include "deps.cpp"                        // json, _json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "post.cpp"                        // post
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string, std::to_string

CurlClient Oanda::Client::cancel_order(order_t *order) {
  CurlClient curl_client = cancel_order(order->id);

  json response = json::parse(curl_client.response.body);

  if (response.contains("orderCancelTransaction")) {
    order->status = order_status_t::ORDER_CANCELLED;
  }

  return curl_client;
}

CurlClient Oanda::Client::cancel_order(const int order_id) {
  if (!order_id) {
    std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  std::string url = this->config.base_url + "/v3/accounts/" +
                    this->config.account_id + "/orders/" +
                    std::to_string(order_id) + "/cancel";

  return post({
      .body = "",
      .method = CurlClient::http_method_t::PUT,
      .url = url,
  });
}

#endif
