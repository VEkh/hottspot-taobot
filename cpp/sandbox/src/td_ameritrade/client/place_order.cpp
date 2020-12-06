#if !defined TD_AMERITRADE__CLIENT_place_order
#define TD_AMERITRADE__CLIENT_place_order

#include "client.h" // TdAmeritrade::Client, stream_format, client_config, tokens
#include "lib/curl_client.cpp"    // CurlClient
#include "lib/formatted.cpp"      // Formatted
#include "td_ameritrade/deps.cpp" // json
#include <iostream>               // std::cout, std::endl
#include <string>                 // std::string, std::to_string

void TdAmeritrade::Client::place_order(json payload) {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "Placing the following order: \n" << payload << std::endl;
  std::cout << fmt.reset;

  CurlClient::props_t curl_props = {
      .body = payload.dump(),
      .body_params = {},
      .debug_flag = (CurlClient::debug_t)props.debug_flag,
      .headers =
          {
              {"Authorization", "Bearer " + tokens.access_token},
              {"Content-Type", "application/json"},
          },
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = "https://api.tdameritrade.com/v1/accounts/" +
             std::to_string(client_config.account_id) + "/orders",
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  std::string response_body = curl_client.response.body;
  json response_json =
      response_body.empty() ? json(response_body) : json::parse(response_body);

  if (response_json.contains("error")) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout << "❌ Order placement failed: \n"
              << response_json.dump(2) << std::endl;
    std::cout << fmt.reset;

    exit(1);
  }

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Order successfully placed!" << std::endl;
  std::cout << fmt.reset;
}

#endif
