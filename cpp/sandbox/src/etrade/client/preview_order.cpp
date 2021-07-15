#ifndef ETRADE__CLIENT_preview_order
#define ETRADE__CLIENT_preview_order

#include "build_preview_order_payload.cpp" // build_preview_order_payload
#include "client.h"        // ETrade::Client, client_config, order_t
#include "etrade/deps.cpp" // json
#include "handle_place_order_error.cpp"           // handle_place_order_error
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include <regex> // std::regex, std::regex_search

namespace ETrade {
namespace preview_order {
bool is_immediate_retry_error(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::cout << fmt.yellow << response_body << fmt.reset << std::endl;

  json response = json::parse(response_body);

  if (response.contains("Error") && response["Error"]["code"] == 1037) {
    return true;
  }

  if (response.contains("Error") &&
      response["Error"]["message"] ==
          "Number of requests exceeded the rate limit set") {
    return true;
  }

  return std::regex_search(response_body,
                           std::regex("oauth_parameters_absent=oauth_nonce"));
}
} // namespace preview_order
} // namespace ETrade

CurlClient ETrade::Client::preview_order(const order_t &order) {
  std::string request_url = client_config.base_url + "/v1/accounts/" +
                            client_config.account_id_key +
                            "/orders/preview.json";

  std::string payload = build_preview_order_payload(order);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return post({
            .body = payload,
            .method = CurlClient::http_method_t::POST,
            .url = request_url,
        });
      },
      ETrade::preview_order::is_immediate_retry_error);

  return handle_place_order_error(curl_client, order.action, "Preview");
}

#endif
