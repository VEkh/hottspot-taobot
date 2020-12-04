#if !defined TD_AMERITRADE__CLIENT_fetch_tokens
#define TD_AMERITRADE__CLIENT_fetch_tokens

#include "client.h" // TOKENS_PATH, TdAmeritrade::Client, debug_t, props, stream_format
#include "lib/curl_client.cpp"        // CurlClient
#include "lib/formatted.cpp"          // Formatted::error_message
#include "td_ameritrade/deps.cpp"     // json
#include "utils/debug.cpp"            // utils::debug
#include "write_response_to_file.cpp" // write_response_to_file
#include <iostream>                   // std::cout, std::endl
#include <map>                        // std::map
#include <string>                     // std::string

void TdAmeritrade::Client::fetch_tokens(
    std::map<std::string, std::string> body_params) {
  CurlClient::props_t curl_props = {
      .body_params = body_params,
      .debug_flag = CurlClient::debug_t::OFF,
      .headers = {{"Content-Type", "application/x-www-form-urlencoded"}},
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = "https://api.tdameritrade.com/v1/oauth2/token",
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  std::string response_body = curl_client.response.body;
  json response = json::parse(response_body);

  if (response.contains("error")) {
    std::string error_message = Formatted::error_message("Request FAILED");

    utils::debug::inspect(error_message);
    std::cout << response << std::endl;

    exit(1);
  }

  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.green << "Successfully fetched tokens"
            << fmt.reset << std::endl;

  if (props.debug_flag == debug_t::ON) {
    std::cout << response_body << std::endl;

    std::cout << fmt.bold << fmt.yellow << "Writing to: " << TOKENS_PATH
              << fmt.reset << std::endl;
  }

  write_response_to_file(response_body, TOKENS_PATH);
}

#endif
