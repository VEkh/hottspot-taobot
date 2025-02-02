#ifndef OANDA__CLIENT_load_config
#define OANDA__CLIENT_load_config

#include "client.h"          // Oanda::Client, config
#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted::error_message
#include "lib/utils/io.cpp"  // ::utils::io
#include <list>              // std::list
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

void Oanda::Client::load_config() {
  std::string config_path =
      std::string(APP_DIR) + "/config/oanda/credentials.json";

  std::string error_message;

  const std::string api_key = this->flags["api-key"];
  json config_json = ::utils::io::load_config("oanda", api_key);

  const std::list<std::string> required_keys = {
      api_key,
  };

  for (const std::string key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    std::string error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  json api_key_json = config_json[api_key];

  const std::list<std::string> nested_required_keys = {
      "account_stop_loss_ratio",
      "authentication_token",
      "base_url",
      "env_symbols",
      "id",
  };

  for (const std::string key : nested_required_keys) {
    if (api_key_json.contains(key)) {
      continue;
    }

    std::string error_message = Formatted::error_message(
        "Config file is missing the `" + api_key + std::string(".") +
        std::string(key) + "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  if (api_key_json.contains("debug_sql")) {
    this->config.debug_sql = (bool)api_key_json["debug_sql"];
  }

  // TODO: Decide
  if (api_key_json.contains("margin_throttle")) {
    this->config.margin_throttle = (double)api_key_json["margin_throttle"];
  }

  // TODO: Decide
  if (api_key_json.contains("reversal_timeframe_minutes")) {
    this->config.reversal_timeframe_minutes =
        (int)api_key_json["reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_stop_profit_once")) {
    this->config.should_stop_profit_once =
        (bool)api_key_json["should_stop_profit_once"];
  }

  // TODO: Decide
  if (api_key_json.contains("spike_entry_score")) {
    this->config.spike_entry_score = (double)api_key_json["spike_entry_score"];
  }

  // TODO: Decide
  if (api_key_json.contains("spike_height_ratio")) {
    this->config.spike_height_ratio =
        (double)api_key_json["spike_height_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("spike_min_price_action")) {
    this->config.spike_min_price_action =
        (double)api_key_json["spike_min_price_action"];
  }

  this->config = {
      .account_id = api_key_json["id"],
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .authentication_token = api_key_json["authentication_token"],
      .base_url = api_key_json["base_url"],
      .debug_sql = this->config.debug_sql,
      .env_symbols = ::utils::io::read_env_symbols(api_key_json),
      .margin_throttle = this->config.margin_throttle, // TODO: Decide
      .reversal_timeframe_minutes =
          this->config.reversal_timeframe_minutes, // TODO: Decide
      .should_stop_profit_once =
          this->config.should_stop_profit_once,              // TODO: Decide
      .spike_entry_score = this->config.spike_entry_score,   // TODO: Decide
      .spike_height_ratio = this->config.spike_height_ratio, // TODO: Decide
      .spike_min_price_action =
          this->config.spike_min_price_action, // TODO: Decide
  };
}

#endif
