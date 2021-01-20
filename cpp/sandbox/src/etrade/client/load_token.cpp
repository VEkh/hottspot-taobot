#if !defined ETRADE__CLIENT_load_token
#define ETRADE__CLIENT_load_token

#include "client.h"                // ETrade::Client, tokens
#include "etrade/deps.cpp"         // json
#include "get_config_filepath.cpp" // get_config_filepath
#include "lib/formatted.cpp"       // Formatted::error_message
#include <fstream>                 // std::ifstream, std::ios
#include <string>                  // std::string

void ETrade::Client::load_token() {
  if (!oauth.token.empty() && !oauth.token_secret.empty()) {
    return;
  }

  std::string tokens_filepath = get_config_filepath("tokens");
  const char *tokens_path = tokens_filepath.c_str();

  std::ifstream tokens_file(tokens_path, std::ios::in);

  if (!tokens_file.good()) {
    std::string error_message = Formatted::error_message(
        "Tokens missing at " + std::string(tokens_path) +
        ". Run `ETrade::Client::fetch_token` first.");

    throw std::invalid_argument(error_message);
  }

  json tokens_json;
  tokens_file >> tokens_json;

  oauth.token = std::string(tokens_json["oauth_token"]);
  oauth.token_secret = std::string(tokens_json["oauth_token_secret"]);
}

#endif
