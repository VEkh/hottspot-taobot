#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"          // Alpaca::Client, config
#include "deps.cpp"          // json
#include "is_beta.cpp"       // is_beta
#include "is_live.cpp"       // is_live
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Alpaca::Client::load_config() {
  std::string config_path =
      std::string(APP_DIR) + "/config/alpaca/credentials.json";

  std::ifstream config_file(config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    std::string error_message = Formatted::error_message(
        "Config file missing at " + std::string(config_path));
    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  const char *required_keys[] = {
      "data_base_url",
      "live",
      "paper",
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

  const char *nested_required_keys[] = {
      "api_key_id",
      "api_secret_key",
      "base_url",
  };

  const char *session_keys[] = {
      "live",
      "paper",
  };

  for (const char *session_key : session_keys) {
    for (const char *key : nested_required_keys) {
      if (config_json[session_key].contains(key)) {
        continue;
      }

      std::string error_message = Formatted::error_message(
          "Config file is missing the `" + std::string(session_key) +
          std::string(".") + std::string(key) +
          "` key. Please ensure it is in the config file at " +
          std::string(config_path));

      throw std::invalid_argument(error_message);
    }
  }

  const char *session_key = is_live() ? "live" : "paper";
  const std::string account_type_prefix = is_beta() ? "beta_" : "";

  this->config = {
      .api_key_id =
          config_json[session_key][account_type_prefix + "api_key_id"],
      .api_secret_key =
          config_json[session_key][account_type_prefix + "api_secret_key"],
      .base_url = config_json[session_key]["base_url"],
      .data_base_url = config_json["data_base_url"],
  };
}

#endif
