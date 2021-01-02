#if !defined ETRADE__STRADDLE_place_order
#define ETRADE__STRADDLE_place_order

#include "build_place_order_payload.cpp"          // build_place_order_payload
#include "etrade/deps.cpp"                        // json
#include "handle_request_error.cpp"               // handle_request_error
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "preview_order.cpp"                      // preview_order
#include "straddle.h" // ETrade::Straddle, etrade_client, order_t

namespace ETrade {
namespace place_order {
bool is_retriable_response(const std::string &response_body) {
  json repsonse = json::parse(response_body);

  if (repsonse.contains("Error") && repsonse["Error"]["code"] == 100) {
    return true;
  }

  return false;
}
} // namespace place_order
} // namespace ETrade

CurlClient ETrade::Straddle::place_order(order_t &order) {
  std::string request_url =
      etrade_client.client_config.base_url + "/v1/accounts/" +
      etrade_client.client_config.account_id_key + "/orders/place.json";

  CurlClient preview_curl_client = preview_order(order);

  std::string payload =
      build_place_order_payload(preview_curl_client.response.body);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return etrade_client.post({
            .body = payload,
            .method = CurlClient::http_method_t::POST,
            .url = request_url,
        });
      },
      ETrade::place_order::is_retriable_response);

  curl_client = handle_request_error(curl_client, order.action, "Place");

  json response = json::parse(curl_client.response.body);

  order.id = response["PlaceOrderResponse"]["OrderIds"][0]["orderId"];
  order.status = order_status_t::ORDER_OPEN;

  return curl_client;
}

#endif
