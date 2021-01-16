#if !defined ETRADE__STRADDLE_fetch_and_set_orders
#define ETRADE__STRADDLE_fetch_and_set_orders

#include "etrade/deps.cpp"                        // json
#include "lib/curl_client/curl_client.h"          // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // request_with_retry
#include "straddle.h" // ETrade::Straddle, etrade_client, placed_orders, symbol
#include <regex>      // std::regex, std::regex_search
#include <string>     // std::string

void ETrade::Straddle::fetch_and_set_orders() {
  std::string url = etrade_client.client_config.base_url + "/v1/accounts/" +
                    etrade_client.client_config.account_id_key +
                    "/orders.json?count=100&symbol=" + std::string(symbol);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return etrade_client.fetch(url); },
      [](const std::string &response) -> bool {
        if (response.empty()) {
          return true;
        }

        if (std::regex_search(response,
                              std::regex("oauth_problem=nonce_used"))) {
          return true;
        }

        return std::regex_search(
            response, std::regex("oauth_parameters_absent=oauth_nonce"));
      });

  placed_orders =
      json::parse(curl_client.response.body)["OrdersResponse"]["Order"];
}

#endif
