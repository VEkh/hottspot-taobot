#ifndef OANDA__CLIENT_cancel_order
#define OANDA__CLIENT_cancel_order

/*
 * Oanda::Client
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
#include <string>                          // std::string, std::to_string

std::string Oanda::Client::cancel_order(order_t *order) {
  std::string response_body = cancel_order(order->id);

  std::cout << fmt.bold << fmt.yellow;
  printf("[OANDA__CLIENT_cancel_order]: CANCEL order response: %s\n",
         response_body.c_str());
  std::cout << fmt.reset << std::endl;

  json response = ::utils::json::parse_with_catch(response_body,
                                                  "OANDA__CLIENT_cancel_order");

  if (response.contains("orderCancelTransaction")) {
    order->status = order_status_t::ORDER_CANCELLED;
  } else if (response.contains("errorCode") &&
             std::string(response["errorCode"]) == "ORDER_DOESNT_EXIST") {
    order->status = order_status_t::ORDER_CANCELLED;
  }

  return response_body;
}

std::string Oanda::Client::cancel_order(const int order_id) {
  if (!order_id) {
    std::string message =
        Formatted::error_message("Please provide an order id");

    throw std::invalid_argument(message);
  }

  std::string url = this->config.base_url + "/v3/accounts/" +
                    this->config.account_id + "/orders/" +
                    std::to_string(order_id) + "/cancel";

  CurlClient curl_client = post({
      .body = "",
      .method = CurlClient::http_method_t::PUT,
      .url = url,
  });

  return curl_client.response.body;
}

#endif
