#if !defined TD_AMERITRADE__CLIENT_load_tokens
#define TD_AMERITRADE__CLIENT_load_tokens

#include "client.h"               // TOKENS_PATH, TdAmeritrade::Client, tokens
#include "lib/formatted.cpp"      // Formatted::error_message
#include "td_ameritrade/deps.cpp" // json
#include <fstream>                // std::ifstream, std::ios
#include <string>                 // std::string

void TdAmeritrade::Client::load_tokens() {
  std::ifstream tokens_file(TOKENS_PATH, std::ios::in);

  if (!tokens_file.good()) {
    std::string error_message = Formatted::error_message(
        "Tokens missing at " + std::string(TOKENS_PATH) +
        ". Run `TdAmeritrade::Client::fetch_tokens` first.");

    throw std::invalid_argument(error_message);
  }

  json tokens_json;
  tokens_file >> tokens_json;

  tokens = {
      .access_token = std::string(tokens_json["access_token"]),
      .refresh_token = std::string(tokens_json["refresh_token"]),
  };
}

#endif
