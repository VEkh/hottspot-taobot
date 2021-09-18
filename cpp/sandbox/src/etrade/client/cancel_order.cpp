#ifndef ETRADE__CLIENT_cancel_order
#define ETRADE__CLIENT_cancel_order

#include "client.h"        // ETrade::Client, config, order_t
#include "etrade/deps.cpp" // json, _json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "post.cpp"                        // post
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

CurlClient ETrade::Client::cancel_order(order_t *order) {
  CurlClient curl_client = cancel_order(order->id);

  json response = json::parse(curl_client.response.body);

  if (response.contains("CancelOrderResponse")) {
    order->status = order_status_t::ORDER_CANCELLED;
  }

  return curl_client;
}

CurlClient ETrade::Client::cancel_order(int order_id) {
  if (!order_id) {
    std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  std::string url = config.base_url + "/v1/accounts/" +
                    config.account_id_key + "/orders/cancel.json";

  json body = R"(
    {
      "CancelOrderRequest": {
        "orderId": 1
      }
    }
  )"_json;

  body["CancelOrderRequest"]["orderId"] = order_id;

  return post({
      .body = body.dump(),
      .method = CurlClient::http_method_t::PUT,
      .url = url,
  });
}

#endif
