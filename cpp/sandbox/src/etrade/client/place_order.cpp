#ifndef ETRADE__CLIENT_place_order
#define ETRADE__CLIENT_place_order

/*
 * ETrade::Client
 * config
 * order_status_t
 * order_t
 */
#include "client.h"

#include "build_place_order_payload.cpp"          // build_place_order_payload
#include "etrade/deps.cpp"                        // json
#include "handle_place_order_error.cpp"           // handle_place_order_error
#include "is_next_cycle_retry_error.cpp"          // is_next_cycle_retry_error
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/json.cpp"                     // ::utils::json
#include "preview_order.cpp"                      // preview_order
#include <regex>  // std::regex, std::regex_search
#include <time.h> // time, time_t

namespace ETrade {
namespace place_order {
bool is_immediate_retry_error(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return true;
  }

  json response = ::utils::json::parse_with_catch(
      response_body, "ETRADE__PLACE_ORDER_is_immediate_retry_error");

  if (response.contains("Error") && response["Error"]["code"] == 163) {
    return true;
  }

  if (std::regex_search(response_body,
                        std::regex("oauth_parameters_absent=oauth_nonce"))) {
    return true;
  }

  return false;
}
} // namespace place_order
} // namespace ETrade

CurlClient ETrade::Client::place_order(order_t *order) {
  std::string request_url = config.base_url + "/v1/accounts/" +
                            config.account_id_key + "/orders/place.json";

  CurlClient preview_curl_client = preview_order(*order);

  if (is_next_cycle_retry_error(preview_curl_client)) {
    return preview_curl_client;
  }

  std::string payload =
      build_place_order_payload(preview_curl_client.response.body);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return post({
            .body = payload,
            .method = CurlClient::http_method_t::POST,
            .url = request_url,
        });
      },
      ETrade::place_order::is_immediate_retry_error);

  curl_client = handle_place_order_error(curl_client, order->action, "Place");

  if (is_next_cycle_retry_error(curl_client)) {
    return curl_client;
  }

  time_t now;
  time(&now);

  json response = ::utils::json::parse_with_catch(curl_client.response.body,
                                                  "ETRADE__CLIENT_place_order");

  order->id = response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
  order->status = order_status_t::ORDER_OPEN;
  order->timestamp = now;

  return curl_client;
}

#endif
