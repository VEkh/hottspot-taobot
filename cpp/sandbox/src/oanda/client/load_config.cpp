#ifndef OANDA__CLIENT_load_config
#define OANDA__CLIENT_load_config

#include "client.h"          // Oanda::Client, config
#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Oanda::Client::load_config() {
  std::string config_path =
      std::string(APP_DIR) + "/config/oanda/credentials.json";

  std::ifstream config_file(config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    std::string error_message = Formatted::error_message(
        "Config file missing at " + std::string(config_path));
    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;

  const char *required_keys[] = {
      "account_id",
      "authentication_token",
      "base_url",
  };

  for (const char *key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    std::string error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  this->config = {
      .account_id = config_json["account_id"],
      .authentication_token = config_json["authentication_token"],
      .base_url = config_json["base_url"],
  };
}

#endif
