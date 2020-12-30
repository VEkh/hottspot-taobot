#if !defined ETRADE__STRADDLE_fetch_and_set_orders
#define ETRADE__STRADDLE_fetch_and_set_orders

#include "lib/curl_client/curl_client.h" // CurlClient
#include "straddle.h" // ETrade::Straddle, etrade_client, placed_orders, symbol
#include <string>     // std::string

void ETrade::Straddle::fetch_and_set_orders() {
  std::string url = etrade_client.client_config.base_url + "/v1/accounts/" +
                    etrade_client.client_config.account_id_key +
                    "/orders.json?symbol=" + std::string(symbol);

  CurlClient curl_client = etrade_client.fetch(url);

  placed_orders =
      json::parse(curl_client.response.body)["OrdersResponse"]["Order"];
}

#endif
