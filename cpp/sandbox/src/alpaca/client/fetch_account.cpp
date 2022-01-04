#ifndef ALPACA__CLIENT_fetch_account
#define ALPACA__CLIENT_fetch_account

#include "client.h"                        // Alpaca::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

std::string Alpaca::Client::fetch_account() {
  std::string request_url = config.base_url + "/v2/account";

  CurlClient curl_client = fetch(request_url);

  return curl_client.response.body;
}

#endif
