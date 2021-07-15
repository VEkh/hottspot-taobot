#ifndef ETRADE__STOCK_BOT_fetch_orders
#define ETRADE__STOCK_BOT_fetch_orders

#include "etrade/deps.cpp"                        // json
#include "lib/curl_client/curl_client.h"          // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // request_with_retry
#include "lib/utils/string.cpp"                   // utils::string
#include "stock_bot.h"                            // ETrade::StockBot
#include <regex>  // std::regex, std::regex_search
#include <string> // std::string

void ETrade::StockBot::fetch_orders() {
  std::string url = this->etrade_client.client_config.base_url +
                    "/v1/accounts/" +
                    this->etrade_client.client_config.account_id_key +
                    "/orders.json?count=100&symbol=" + std::string(symbol);

  CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient { return this->etrade_client.fetch(url); },
      [](const CurlClient &curl_client) -> bool {
        const std::string response = curl_client.response.body;

        if (std::regex_search(response,
                              std::regex("oauth_problem=nonce_used"))) {
          return true;
        }

        return std::regex_search(
            response, std::regex("oauth_parameters_absent=oauth_nonce"));
      });

  if (curl_client.response.body.empty()) {
    return;
  }

  this->placed_orders =
      json::parse(curl_client.response.body)["OrdersResponse"]["Order"];
}

#endif
