#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"          // Alpaca::Client, config
#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Alpaca::Client::load_config() {
  std::string config_path =
      std::string(APP_DIR) + "/config/alpaca/credentials.json";
  std::string error_message;

  std::ifstream config_file(config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    error_message = Formatted::error_message("Config file missing at " +
                                             std::string(config_path));
    throw std::invalid_argument(error_message);
  }

  const std::string api_key_id = this->flags["api_key_id"];

  if (api_key_id.empty()) {
    error_message = Formatted::error_message(
        "Please provide an --api_key_id=<API_KEY_ID> option");

    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  if (!config_json.contains(api_key_id)) {
    error_message = Formatted::error_message(
        "There is no entry for the `api_key_id` \"" + api_key_id + "\"");

    throw std::invalid_argument(error_message);
  }

  const char *required_keys[] = {
      "data_base_url",
      api_key_id.c_str(),
  };

  for (const char *key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  const char *nested_required_keys[] = {
      "base_url",
      "is_live",
      "secret_key",
  };

  for (const char *key : nested_required_keys) {
    if (config_json[api_key_id].contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + api_key_id + std::string(".") +
        std::string(key) + "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  this->config = {
      .api_key_id = api_key_id,
      .api_secret_key = config_json[api_key_id]["secret_key"],
      .base_url = config_json[api_key_id]["base_url"],
      .data_base_url = config_json["data_base_url"],
      .is_live = config_json[api_key_id]["is_live"],
  };
}

#endif
