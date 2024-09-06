#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"          // Alpaca::Client
#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted::error_message
#include "lib/utils/io.cpp"  // ::utils::io
#include <list>              // std::list
#include <map>               // std::map
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string
#include <time.h>            // mktime, time, tm

void Alpaca::Client::load_config() {
  const std::string config_path =
      std::string(APP_DIR) + "/config/alpaca/credentials.json";

  std::string error_message;

  const std::string api_key = this->flags["api-key"];
  json config_json = ::utils::io::load_config("alpaca", api_key);

  const std::list<std::string> required_keys = {
      "data_base_url",
      api_key,
  };

  for (const std::string key : required_keys) {
    if (config_json.contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + std::string(key) +
        "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  json api_key_json = config_json[api_key];

  const std::list<std::string> nested_required_keys = {
      "account_stop_loss_ratio",    "base_url",   "env_symbols", "is_live",
      "reversal_timeframe_minutes", "secret_key",
  };

  for (const std::string key : nested_required_keys) {
    if (api_key_json.contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + api_key + std::string(".") +
        std::string(key) + "` key. Please ensure it is in the config file at " +
        std::string(config_path));

    throw std::invalid_argument(error_message);
  }

  if (api_key_json.contains("debug_sql")) {
    config.debug_sql = (bool)api_key_json["debug_sql"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_always_reverse_profit")) {
    config.should_always_reverse_profit =
        (bool)api_key_json["should_always_reverse_profit"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_market_open_trend_start")) {
    config.should_market_open_trend_start =
        (bool)api_key_json["should_market_open_trend_start"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_stop_loss")) {
    config.should_stop_loss = (bool)api_key_json["should_stop_loss"];
  }

  this->config = {
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .api_key = api_key,
      .api_key_id = api_key_json["id"],
      .api_secret_key = api_key_json["secret_key"],
      .base_url = api_key_json["base_url"],
      .data_base_url = config_json["data_base_url"],
      .debug_sql = config.debug_sql,
      .env_symbols = ::utils::io::read_env_symbols(api_key_json),
      .is_live = api_key_json["is_live"],
      .reversal_timeframe_minutes =
          (int)api_key_json["reversal_timeframe_minutes"],
      .should_always_reverse_profit =
          config.should_always_reverse_profit, // TODO: Decide
      .should_market_open_trend_start =
          config.should_market_open_trend_start,   // TODO: Decide
      .should_stop_loss = config.should_stop_loss, // TODO: Decide
  };
}

#endif
