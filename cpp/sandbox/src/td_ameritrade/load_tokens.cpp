#if !defined TD_AMERITRADE_CLIENT__LOAD_TOKENS
#define TD_AMERITRADE_CLIENT__LOAD_TOKENS

#if !defined DEPENDENCY_SIMDJSON
#include "deps/simdjson/simdjson.cpp" // simdjson
#endif

#include "build_error_message.cpp" // build_error_message
#include "td_ameritrade_client.h" // TOKENS_PATH, TdAmeritradeClient, json_parser, tokens
#include <fstream>                // std::ifstream, std::ios
#include <string>                 // std::string

void TdAmeritradeClient::load_tokens() {
  std::ifstream tokens_file(TOKENS_PATH, std::ios::in);

  if (!tokens_file.good()) {
    std::string error_message =
        build_error_message("Tokens missing at " + std::string(TOKENS_PATH) +
                            ". Run `TdAmeritradeClient::fetch_tokens` first.");

    throw std::invalid_argument(error_message);
  }

  simdjson::dom::element tokens_json = json_parser.load(TOKENS_PATH);

  tokens = {
      .access_token = std::string(tokens_json["access_token"]),
      .refresh_token = std::string(tokens_json["refresh_token"]),
  };
}

#endif
