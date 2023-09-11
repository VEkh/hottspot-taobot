#ifndef OANDA__CLIENT_fetch_order
#define OANDA__CLIENT_fetch_order

#include "client.h"                               // Oanda::Client
#include "fetch.cpp"                              // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/json.cpp"                     // ::utils::json
#include <string>                                 // std::string

namespace Oanda {
namespace fetch_order {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  return response_body.empty();
}
} // namespace fetch_order
} // namespace Oanda

std::string Oanda::Client::fetch_order(const int order_id) {
  std::string request_url = config.base_url + "/v3/accounts/" +
                            config.account_id + "/orders/" +
                            std::to_string(order_id);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        return fetch({.timeout_seconds = 0, .url = request_url});
      },
      Oanda::fetch_order::is_retriable_response);

  std::string response_body = curl_client.response.body;

  json response = ::utils::json::parse_with_catch(response_body,
                                                  "OANDA__CLIENT_fetch_order");

  return response["order"].dump();
}

#endif
