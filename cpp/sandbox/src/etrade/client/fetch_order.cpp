#ifndef ETRADE__CLIENT_fetch_order
#define ETRADE__CLIENT_fetch_order

#include "client.h"                               // ETrade::Client, config
#include "etrade/deps.cpp"                        // json
#include "fetch.cpp"                              // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include <regex>  // std::regex, std::regex_search
#include <string> // std::string, std::to_string

namespace ETrade {
namespace fetch_order {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return false;
  }

  json response = json::parse(response_body);

  if (!response.contains("OrdersResponse")) {
    return true;
  }

  if (std::regex_search(response_body,
                        std::regex("oauth_parameters_absent=oauth_nonce"))) {
    return true;
  }

  if (std::regex_search(response_body,
                        std::regex("oauth_problem=nonce_used"))) {
    return true;
  }

  return false;
}
} // namespace fetch_order
} // namespace ETrade

std::string ETrade::Client::fetch_order(const int order_id) {
  std::string request_url = config.base_url + "/v1/accounts/" +
                            config.account_id_key + "/orders/" +
                            std::to_string(order_id) + ".json";

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return fetch(request_url); },
      ETrade::fetch_order::is_retriable_response);

  std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return response_body;
  }

  json response = json::parse(response_body);

  return response["OrdersResponse"]["Order"][0].dump();
}

#endif
