#ifndef ALPACA__CLIENT_fetch_order
#define ALPACA__CLIENT_fetch_order

#include "client.h"                        // Alpaca::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/json.cpp"              // ::utils::json
#include <string>                          // std::string

std::string Alpaca::Client::fetch_order(const std::string &order_id) {
  std::string request_url = config.base_url + "/v2/orders/" + order_id;

  CurlClient curl_client = fetch({.timeout_seconds = 0, .url = request_url});

  return curl_client.response.body;
}

#endif
