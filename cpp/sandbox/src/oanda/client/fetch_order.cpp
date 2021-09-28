#ifndef OANDA__CLIENT_fetch_order
#define OANDA__CLIENT_fetch_order

#include "client.h"                        // Oanda::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

std::string Oanda::Client::fetch_order(const int order_id) {
  std::string request_url = config.base_url + "/v3/accounts/" +
                            config.account_id + "/orders/" +
                            std::to_string(order_id);

  CurlClient curl_client = fetch(request_url);

  std::string response_body = curl_client.response.body;
  json response = json::parse(response_body);

  return response["order"].dump();
}

#endif
