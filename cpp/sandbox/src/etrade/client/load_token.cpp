#if !defined ETRADE__CLIENT_load_token
#define ETRADE__CLIENT_load_token

#include "client.h"          // TOKENS_PATH, ETrade::Client, tokens
#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <string>            // std::string

void ETrade::Client::load_token() {
  std::ifstream tokens_file(TOKENS_PATH, std::ios::in);

  if (!tokens_file.good()) {
    std::string error_message = Formatted::error_message(
        "Tokens missing at " + std::string(TOKENS_PATH) +
        ". Run `ETrade::Client::fetch_tokens` first.");

    throw std::invalid_argument(error_message);
  }

  json tokens_json;
  tokens_file >> tokens_json;

  oauth.token = std::string(tokens_json["oauth_token"]);
  oauth.token_secret = std::string(tokens_json["oauth_token_secret"]);
}

#endif
