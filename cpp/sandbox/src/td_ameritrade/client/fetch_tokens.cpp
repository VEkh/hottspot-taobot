#if !defined TD_AMERITRADE__CLIENT_fetch_tokens
#define TD_AMERITRADE__CLIENT_fetch_tokens

#include "client.h" // TOKENS_PATH, TdAmeritrade::Client, client_config, debug_t, props, stream_format
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted::error_message
#include "lib/utils/debug.cpp"             // utils::debug
#include "lib/utils/io.cpp"                // utils::io
#include "lib/utils/map.cpp"               // utils::map
#include "td_ameritrade/deps.cpp"          // json
#include <iostream>                        // std::cout, std::endl
#include <map>                             // std::map
#include <stdexcept>                       // std::invalid_argument
#include <string>                          // std::string

const char *request_action(std::map<std::string, std::string> params) {
  std::string grant_type = params["grant_type"];

  if (grant_type == "authorization_code") {
    return "fetch";
  }

  if (grant_type == "refresh_token") {
    return "refresh";
  }

  std::string error_message = Formatted::error_message(
      "Unknown token action (grant_type): " + grant_type);

  throw std::invalid_argument(error_message);
}

void TdAmeritrade::Client::fetch_tokens(
    std::map<std::string, std::string> body_params) {
  std::map<std::string, std::string> merged_params = utils::map::merge(
      body_params, {
                       {"access_type", "offline"},
                       {"client_id", client_config.client_id},
                       {"redirect_uri", client_config.redirect_uri},
                   });

  CurlClient::props_t curl_props = {
      .body = "",
      .body_params = merged_params,
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers = {{"Content-Type", "application/x-www-form-urlencoded"}},
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = "https://api.tdameritrade.com/v1/oauth2/token",
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  const char *action = request_action(merged_params);
  Formatted::fmt_stream_t fmt = stream_format;
  std::string response_body = curl_client.response.body;
  json response = json::parse(response_body);

  if (response.contains("error")) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "❌ Failed to " << action << " tokens: " << std::endl;
    std::cout << response_body << std::endl;
    std::cout << fmt.reset << std::endl;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green;
  std::cout << "✅ Successfully " << action << "ed tokens." << std::endl;
  std::cout << fmt.reset;

  if (props.debug_flag == debug_t::ON) {
    std::cout << response_body << std::endl;

    std::cout << fmt.bold << fmt.yellow << "Writing to: " << TOKENS_PATH
              << fmt.reset << std::endl;
  }

  utils::io::write_to_file(response.dump(2), TOKENS_PATH);
}

#endif
