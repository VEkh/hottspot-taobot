#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"           // Alpaca::Client
#include "deps.cpp"           // json
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/io.cpp"   // ::utils::io
#include "lib/utils/time.cpp" // ::utils::time_
#include <map>                // std::map
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string
#include <time.h>             // mktime, time, tm

void Alpaca::Client::load_config() {
  const std::string config_path =
      std::string(APP_DIR) + "/config/alpaca/credentials.json";

  std::string error_message;

  const std::string api_key = this->flags["api-key"];
  json config_json = ::utils::io::load_config("alpaca", api_key);

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

  json api_key_json = config_json[api_key];

  std::vector<std::string> nested_required_keys = {
      "account_stop_loss_ratio", "base_url",   "is_live",
      "late_start_seconds",      "secret_key",
  };

  for (std::string key : nested_required_keys) {
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

  if (api_key_json.contains("reversal_timeframe_minutes")) {
    config.reversal_timeframe_minutes =
        (int)api_key_json["reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("peak_padding_ratio")) {
    config.peak_padding_ratio = (double)api_key_json["peak_padding_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("reverse_profit_during")) {
    config.reverse_profit_during =
        (std::string)api_key_json["reverse_profit_during"];
  }

  if (api_key_json.contains("secondary_reversal_timeframe_minutes")) {
    config.secondary_reversal_timeframe_minutes =
        (int)api_key_json["secondary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_asymmetric_reversal")) {
    config.should_await_asymmetric_reversal =
        (bool)api_key_json["should_await_asymmetric_reversal"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_symmetric_reversal")) {
    config.should_await_symmetric_reversal =
        (bool)api_key_json["should_await_symmetric_reversal"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_hold_first_position")) {
    config.should_hold_first_position =
        (bool)api_key_json["should_hold_first_position"];
  }

  // TODO: Decide
  if (api_key_json.contains("tertiary_reversal_timeframe_minutes")) {
    config.tertiary_reversal_timeframe_minutes =
        (int)api_key_json["tertiary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("trend_slip_percentile")) {
    config.trend_slip_percentile =
        (double)api_key_json["trend_slip_percentile"];
  }

  // TODO: Decide
  if (api_key_json.contains("win_percentile")) {
    config.win_percentile = (double)api_key_json["win_percentile"];
  }

  this->config = {
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .api_key = api_key,
      .api_key_id = api_key_json["id"],
      .api_secret_key = api_key_json["secret_key"],
      .base_url = api_key_json["base_url"],
      .data_base_url = config_json["data_base_url"],
      .debug_sql = config.debug_sql,
      .is_live = api_key_json["is_live"],
      .late_start_seconds = api_key_json["late_start_seconds"],
      .peak_padding_ratio = config.peak_padding_ratio, // TODO: Decide
      .reversal_timeframe_minutes = config.reversal_timeframe_minutes,
      .reverse_profit_during = config.reverse_profit_during, // TODO: Decide
      .secondary_reversal_timeframe_minutes =
          config.secondary_reversal_timeframe_minutes,
      .should_await_asymmetric_reversal =
          config.should_await_asymmetric_reversal, // TODO: Decide
      .should_await_symmetric_reversal =
          config.should_await_symmetric_reversal, // TODO: Decide
      .should_hold_first_position =
          config.should_hold_first_position, // TODO: Decide
      .tertiary_reversal_timeframe_minutes =
          config.tertiary_reversal_timeframe_minutes,        // TODO: Decide
      .trend_slip_percentile = config.trend_slip_percentile, // TODO: Decide
      .win_percentile = config.win_percentile,               // TODO: Decide
  };
}

#endif
