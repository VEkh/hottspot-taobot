#ifndef ETRADE__CLIENT_fetch_account_snapshot
#define ETRADE__CLIENT_fetch_account_snapshot

#include "client.h"                               // ETrade::Client, config
#include "etrade/deps.cpp"                        // json
#include "fetch.cpp"                              // fetch
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/utils/json.cpp"                     // ::utils::json
#include <regex>  // std::regex, std::regex_search
#include <string> // std::string

namespace ETrade {
namespace fetch_account_snapshot {
bool is_retriable_response(const CurlClient &curl_client) {
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    return true;
  }

  json response = ::utils::json::parse_with_catch(
      response_body, "ETRADE__FETCH_ACCOUNT_SNAPSHOT_is_retriable_response");

  if (!response.contains("BalanceResponse")) {
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
} // namespace fetch_account_snapshot
} // namespace ETrade

std::string ETrade::Client::fetch_account_snapshot() {
  std::string request_url = config.base_url + "/v1/accounts/" +
                            config.account_id_key +
                            "/balance.json?instType=BROKERAGE&realTimeNAV=true";

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return fetch(request_url); },
      ETrade::fetch_account_snapshot::is_retriable_response);

  std::string response_body = curl_client.response.body;

  return response_body;
}

#endif
