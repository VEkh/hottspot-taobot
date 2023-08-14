#ifndef OANDA__CLIENT_fetch
#define OANDA__CLIENT_fetch

#include "client.h"                               // Oanda::Client
#include "lib/curl_client/curl_client.cpp"        // CurlClient
#include "lib/curl_client/request_with_retry.cpp" // CurlClient::request_with_retry
#include "lib/formatted.cpp"                      // Formatted
#include <regex>     // std::regex, std::regex_search
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

namespace Oanda {
namespace fetch {
bool is_immediate_retry_error(const CurlClient &curl_client) {
  const Formatted::fmt_stream_t fmt = Formatted::stream();
  const std::string response_body = curl_client.response.body;

  if (response_body.empty()) {
    std::cout << fmt.bold << fmt.yellow;
    printf("[OANDA__CLIENT_fetch] %s response empty.\n",
           curl_client.props.url.c_str());
    std::cout << fmt.reset << std::endl;

    return true;
  }

  if (std::regex_search(response_body, std::regex("<html>"))) {
    std::cout << fmt.bold << fmt.yellow;
    printf("[OANDA__CLIENT_fetch] HTML response @ %s: %s\n",
           curl_client.props.url.c_str(), response_body.c_str());
    std::cout << fmt.reset << std::endl;

    return true;
  };

  return false;
}
} // namespace fetch
} // namespace Oanda

CurlClient Oanda::Client::fetch(std::string url) {
  if (url.empty()) {
    std::string error_message =
        Formatted::error_message("Please provide a url.");

    throw std::invalid_argument(error_message);
  }

  const CurlClient curl_client = CurlClient::request_with_retry(
      [&]() -> CurlClient {
        CurlClient client = CurlClient({
            .body = "",
            .body_params = {},
            .debug_flag = CurlClient::debug_t::OFF,
            .headers =
                {
                    {"Authorization", std::string("Bearer ") +
                                          this->config.authentication_token},
                },
            .method = CurlClient::http_method_t::GET,
            .query_params = {},
            .url = url,
        });

        client.request();

        return client;
      },
      Oanda::fetch::is_immediate_retry_error);

  return curl_client;
}

#endif
