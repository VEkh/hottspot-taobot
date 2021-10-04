#ifndef OANDA__CLIENT_fetch_account
#define OANDA__CLIENT_fetch_account

#include "client.h"                        // Oanda::Client
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

std::string Oanda::Client::fetch_account() {
  std::string request_url =
      config.base_url + "/v3/accounts/" + config.account_id + "/summary";

  CurlClient curl_client = fetch(request_url);

  return curl_client.response.body;
}

#endif
