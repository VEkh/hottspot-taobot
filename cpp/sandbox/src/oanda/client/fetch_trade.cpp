#ifndef OANDA__CLIENT_fetch_trade
#define OANDA__CLIENT_fetch_trade

#include "client.h"                        // Oanda::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/utils/json.cpp"              // ::utils::json
#include <string>                          // std::string

std::string Oanda::Client::fetch_trade(const int trade_id) {
  std::string request_url = config.base_url + "/v3/accounts/" +
                            config.account_id + "/trades/" +
                            std::to_string(trade_id);

  CurlClient curl_client = fetch(request_url);

  std::string response_body = curl_client.response.body;
  json response = ::utils::json::parse_with_catch(response_body,
                                                  "OANDA__CLIENT_fetch_trade");

  return response["trade"].dump();
}

#endif
