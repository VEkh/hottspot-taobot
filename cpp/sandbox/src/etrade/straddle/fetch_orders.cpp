#if !defined ETRADE__STRADDLE_fetch_orders
#define ETRADE__STRADDLE_fetch_orders

#include "lib/curl_client/curl_client.h" // CurlClient
#include "lib/formatted.cpp"             // Formatted
#include "straddle.h" // ETrade::Straddle, etrade_client, placed_orders, stream_format, symbol
#include <iostream> // std::cout, std::endl
#include <string>   // std::string

void ETrade::Straddle::fetch_orders() {
  Formatted::fmt_stream_t fmt = stream_format;
  std::string url = etrade_client.client_config.base_url + "/v1/accounts/" +
                    etrade_client.client_config.account_id_key +
                    "/orders.json?symbol=" + std::string(symbol);

  std::cout << fmt.bold << fmt.cyan;
  std::cout << "Fetching " << symbol << " orders." << std::endl;
  std::cout << fmt.reset;

  CurlClient curl_client = etrade_client.fetch(url);

  placed_orders =
      json::parse(curl_client.response.body)["OrdersResponse"]["Order"];
}

#endif
