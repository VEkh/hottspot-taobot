#ifndef OANDA__CLIENT_fetch_instrument
#define OANDA__CLIENT_fetch_instrument

#include "client.h"                        // Oanda::Client
#include "deps.cpp"                        // json, nlohmann
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <string>                          // std::string

std::string Oanda::Client::fetch_instrument(const std::string symbol) {
  const std::string request_url = config.base_url + "/v3/accounts/" +
                                  config.account_id +
                                  "/instruments?instruments=" + symbol;

  const CurlClient curl_client = fetch(request_url);

  const std::string response_body = curl_client.response.body;
  json out;
  json response_json;

  try {
    response_json = json::parse(response_body);
    out = response_json["instruments"][0];
  } catch (nlohmann::detail::parse_error &) {
    const std::string error_message = Formatted::error_message(
        std::string("[OANDA__CLIENT_fetch_instrument] Error parsing: ") +
        response_body);

    std::cout << error_message << std::endl;

    return fetch_instrument(symbol);
  }

  return out.dump();
}

#endif
