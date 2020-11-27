#if !defined TD_AMERITRADE_CLIENT__FETCH_TOKENS
#define TD_AMERITRADE_CLIENT__FETCH_TOKENS

#if !defined DEPENDENCY_SIMDJSON
#include "deps/simdjson/simdjson.cpp" // simdjson
#endif

#include "curl_client.cpp"        // CurlClient
#include "td_ameritrade_client.h" // TOKENS_PATH, TdAmeritradeClient, stream_format
#include "utils/uri.cpp"          // utils::debugger
#include "write_response_to_file.cpp" // write_response_to_file
#include <iostream>                   // std::cout, std::endl
#include <map>                        // std::map
#include <string>                     // std::string

void TdAmeritradeClient::fetch_tokens(
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
  simdjson::dom::element response = json_parser.parse(response_body);

  simdjson::dom::element error_message;
  auto json_error = response["error"].get(error_message);

  if (!json_error) {
    std::string error_message = build_error_message("Request FAILED");

    utils::debugger::inspect(error_message);
    std::cout << response << std::endl;

    exit(1);
  }

  std::cout << stream_format.bold << stream_format.green
            << "Successfully fetched tokens: \n"
            << stream_format.reset << response_body << std::endl;

  std::cout << "Writing to: " << TOKENS_PATH << std::endl;

  write_response_to_file(response_body, TOKENS_PATH);
}

#endif
