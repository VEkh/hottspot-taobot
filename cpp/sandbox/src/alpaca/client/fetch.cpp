#ifndef ALPACA__CLIENT_fetch
#define ALPACA__CLIENT_fetch

#include "client.h"                        // Alpaca::Client, fmt
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include <iostream>                        // std::cout, std::endl
#include <regex>                           // std::regex, std::regex_search
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string
#include <unistd.h>                        // usleep

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

  if (std::regex_search(curl_client.response.body,
                        std::regex("rate limit exceeded"))) {
    std::cout << fmt.bold << fmt.yellow;
    puts("[ALPACA__CLIENT_fetch] Rate limit exceeded. Trying again in 500ms");
    std::cout << fmt.reset << std::endl;

    usleep(0.5e6);

    return fetch(url);
  }

  return curl_client;
}

#endif
