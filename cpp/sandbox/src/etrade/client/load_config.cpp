#ifndef ETRADE__CLIENT_load_config
#define ETRADE__CLIENT_load_config

#include "client.h"                // ETrade::Client, config
#include "etrade/deps.cpp"         // json
#include "get_config_filepath.cpp" // get_config_filepath
#include "lib/formatted.cpp"       // Formatted::error_message
#include <fstream>                 // std::ifstream, std::ios
#include <stdexcept>               // std::invalid_argument
#include <string>                  // std::string

void ETrade::Client::load_config() {
  std::string config_path = get_config_filepath("config");
  std::ifstream config_file(config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    std::string error_message =
        Formatted::error_message("Config file missing at " + config_path);
    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  const char *required_keys[] = {
      "account_id",         "account_id_key",        "base_url",
      "oauth_consumer_key", "oauth_consumer_secret",
  };

  for (const char *key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    std::string error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " + config_path);

    throw std::invalid_argument(error_message);
  }

  this->config = {
      .account_id = config_json["account_id"],
      .account_id_key = config_json["account_id_key"],
      .base_url = config_json["base_url"],
  };

  this->oauth = {
      .consumer_key = config_json["oauth_consumer_key"],
      .consumer_secret = config_json["oauth_consumer_secret"],
  };
}

#endif
