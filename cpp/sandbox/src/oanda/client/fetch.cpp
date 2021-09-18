#ifndef OANDA__CLIENT_fetch
#define OANDA__CLIENT_fetch

#include "client.h"                        // Oanda::Client
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

CurlClient Oanda::Client::fetch(std::string url) {
  if (url.empty()) {
    std::string error_message =
        Formatted::error_message("Please provide a url.");

    throw std::invalid_argument(error_message);
  }

  CurlClient curl_client = CurlClient({
      .body = "",
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers = {{"Authorization",
                   std::string("Bearer ") + this->config.authentication_token}},
      .method = CurlClient::http_method_t::GET,
      .query_params = {},
      .url = url,
  });

  curl_client.request();

  return curl_client;
}

#endif
