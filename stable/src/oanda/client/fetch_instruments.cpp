#ifndef OANDA__CLIENT_fetch_instruments
#define OANDA__CLIENT_fetch_instruments

#include "client.h"                        // Oanda::Client
#include "deps.cpp"                        // json, nlohmann
#include "fetch.cpp"                       // fetch
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "lib/utils/vector.cpp"            // ::utils::vector
#include <string>                          // std::string
#include <vector>                          // std::vector

std::string
Oanda::Client::fetch_instruments(const std::vector<std::string> symbols) {
  const std::string symbols_string = ::utils::vector::join(symbols, ",");

  const std::string request_url = config.base_url + "/v3/accounts/" +
                                  config.account_id +
                                  "/instruments?instruments=" + symbols_string;

  const CurlClient curl_client = fetch(request_url);

  const std::string response_body = curl_client.response.body;
  json out;

  try {
    json response_json = json::parse(response_body);
    json instruments = response_json["instruments"];

    for (json::iterator it = instruments.begin(); it != instruments.end();
         it++) {
      out[it.value()["name"]] = it.value();
    }

  } catch (nlohmann::detail::parse_error &) {
    const std::string error_message = Formatted::error_message(
        std::string("[OANDA__CLIENT_fetch_instruments] Error parsing: ") +
        response_body);

    std::cout << error_message << std::endl;

    return fetch_instruments(symbols);
  }

  return out.dump();
}

#endif
