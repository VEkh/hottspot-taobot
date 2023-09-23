#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"           // Alpaca::Client
#include "deps.cpp"           // json
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/time.cpp" // ::utils::time_
#include <fstream>            // std::ifstream, std::ios
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string
#include <time.h>             // mktime, time, tm

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

  const std::string api_key = this->flags["api-key"];

  if (api_key.empty()) {
    error_message = Formatted::error_message(
        "Please provide an --api-key=<API_KEY> option");

    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;
  config_file.close();

  if (!config_json.contains(api_key)) {
    error_message = Formatted::error_message(
        "There is no entry for the `api-key` \"" + api_key + "\"");

    throw std::invalid_argument(error_message);
  }

  const char *required_keys[] = {
      "data_base_url",
      api_key.c_str(),
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

  std::vector<std::string> nested_required_keys = {
      "base_url",
      "is_live",
      "secret_key",
  };

  for (std::string key : nested_required_keys) {
    if (config_json[api_key].contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + api_key + std::string(".") +
        std::string(key) + "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  const bool ml__on_demand_predictions =
      config_json[api_key].contains("ml__on_demand_predictions")
          ? (bool)config_json[api_key]["ml__on_demand_predictions"]
          : this->config.ml__on_demand_predictions;

  this->config = {
      .api_key = api_key,
      .api_key_id = config_json[api_key]["id"],
      .api_secret_key = config_json[api_key]["secret_key"],
      .base_url = config_json[api_key]["base_url"],
      .data_base_url = config_json["data_base_url"],
      .is_live = config_json[api_key]["is_live"],
      .ml__on_demand_predictions = ml__on_demand_predictions,
  };
}

#endif
