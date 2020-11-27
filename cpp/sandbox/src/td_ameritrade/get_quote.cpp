#if !defined TD_AMERITRADE_CLIENT__GET_QUOTE
#define TD_AMERITRADE_CLIENT__GET_QUOTE

#include "build_error_message.cpp" // build_error_message
#include "curl_client.cpp"         // CurlClient
#include "load_tokens.cpp"         // load_tokens
#include "td_ameritrade_client.h"  // TdAmeritradeClient, tokens
#include "utils/debugger.cpp"      // utils::debugger
#include <stdexcept>               // std::invalid_argument
#include <string>                  // std::string

void TdAmeritradeClient::get_quote(char *symbol) {
  if (symbol == nullptr) {
    std::string error_message =
        build_error_message("Please provide a stock symbol");

    throw std::invalid_argument(error_message);
  }

  get_quote(std::string(symbol));
}

void TdAmeritradeClient::get_quote(std::string symbol) {
  load_tokens();

  CurlClient::props_t props = {
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"Authorization", "Bearer " + tokens.access_token},
              {"Content-Type", "application/json"},
          },
      .method = CurlClient::http_method_t::GET,
      .query_params =
          {
              {"frequency", "1"},
              {"frequencyType", "daily"},
              {"period", "1"},
              {"periodType", "month"},
          },
      .url = "https://api.tdameritrade.com/v1/marketdata/" + symbol + "/quotes",
  };

  CurlClient curl_client(props);
  curl_client.request();

  utils::debugger::inspect(curl_client.response.body);
}

#endif
