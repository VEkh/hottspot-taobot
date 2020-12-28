#if !defined ETRADE__CLIENT_cancel_order
#define ETRADE__CLIENT_cancel_order

#include "client.h"                        // ETrade::Client, client_config
#include "etrade/deps.cpp"                 // json, _json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "post.cpp"                        // post
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

CurlClient ETrade::Client::cancel_order(int order_id) {
  if (!order_id) {
    std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  std::string url = client_config.base_url + "/accounts/" +
                    client_config.account_id_key + "/orders/cancel.json";

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
