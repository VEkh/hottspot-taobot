#ifndef ALPACA__CLIENT_fetch
#define ALPACA__CLIENT_fetch

#include "client.h"                        // Alpaca::Client
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

CurlClient Alpaca::Client::fetch(std::string url) {
  if (url.empty()) {
    std::string error_message =
        Formatted::error_message("Please provide a url.");

    throw std::invalid_argument(error_message);
  }

  CurlClient curl_client = CurlClient({
      .body = "",
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"APCA-API-KEY-ID", this->config.api_key_id},
              {"APCA-API-SECRET-KEY", this->config.api_secret_key},
          },
      .method = CurlClient::http_method_t::GET,
      .query_params = {},
      .url = url,
  });

  curl_client.request();

  return curl_client;
}

#endif
