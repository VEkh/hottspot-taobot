#if !defined ETRADE__STRADDLE_preview_order
#define ETRADE__STRADDLE_preview_order

#include "build_preview_order_payload.cpp"        // build_preview_order_payload
#include "etrade/deps.cpp"                        // json
#include "handle_request_error.cpp"               // handle_request_error
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "straddle.h" // ETrade::Straddle, etrade_client, order_t
#include <regex>      // std::regex, std::regex_search

namespace ETrade {
namespace preview_order {
bool is_retriable_response(const std::string &response_body) {
  json repsonse = json::parse(response_body);

  if (repsonse.contains("Error") && repsonse["Error"]["code"] == 1037) {
    return true;
  }

  if (repsonse.contains("Error") && repsonse["Error"]["code"] == 100) {
    return true;
  }

  return std::regex_search(response_body,
                           std::regex("oauth_parameters_absent=oauth_nonce"));
}
} // namespace preview_order
} // namespace ETrade

CurlClient ETrade::Straddle::preview_order(const order_t &order) {
  std::string request_url =
      etrade_client.client_config.base_url + "/v1/accounts/" +
      etrade_client.client_config.account_id_key + "/orders/preview.json";

  std::string payload = build_preview_order_payload(order);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return etrade_client.post({
            .body = payload,
            .method = CurlClient::http_method_t::POST,
            .url = request_url,
        });
      },
      ETrade::preview_order::is_retriable_response);

  return handle_request_error(curl_client, order.action, "Preview");
}

#endif
