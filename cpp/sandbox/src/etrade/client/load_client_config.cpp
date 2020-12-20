#if !defined ETRADE__CLIENT_load_client_config
#define ETRADE__CLIENT_load_client_config

#include "client.h"          // CONFIG_PATH, ETrade::Client, client_config
#include "etrade/deps.cpp"   // json
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void ETrade::Client::load_client_config() {
  std::ifstream config_file(CONFIG_PATH, std::ios::in);

  if (!config_file.good()) {
    std::string error_message = Formatted::error_message(
        "Config file missing at " + std::string(CONFIG_PATH));
    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;

  const char *required_keys[] = {
      "account_id",
      "account_id_key",
      "oauth_consumer_key",
      "oauth_consumer_secret",
  };

  for (const char *key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    std::string error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " +
        std::string(CONFIG_PATH));

    throw std::invalid_argument(error_message);
  }

  client_config = {
      .account_id = config_json["account_id"],
      .account_id_key = config_json["account_id_key"],
  };

  oauth = {
      .consumer_key = config_json["oauth_consumer_key"],
      .consumer_secret = config_json["oauth_consumer_secret"],
  };
}

#endif
