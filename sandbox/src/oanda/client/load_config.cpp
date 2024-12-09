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
      "reversal_timeframe_minutes",
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
  if (api_key_json.contains("market_duration_hours")) {
    this->config.market_duration_hours =
        (int)api_key_json["market_duration_hours"];
  }

  // TODO: Decide
  if (api_key_json.contains("max_slow_reverse_loss_count")) {
    this->config.max_slow_reverse_loss_count =
        (int)api_key_json["max_slow_reverse_loss_count"];
  }

  // TODO: Decide
  if (api_key_json.contains("reversal_proximity_ratio")) {
    this->config.reversal_proximity_ratio =
        (double)api_key_json["reversal_proximity_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("secondary_reversal_timeframe_minutes")) {
    this->config.secondary_reversal_timeframe_minutes =
        (int)api_key_json["secondary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_always_reverse_loss")) {
    this->config.should_always_reverse_loss =
        (bool)api_key_json["should_always_reverse_loss"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_complete_spike")) {
    this->config.should_await_complete_spike =
        (bool)api_key_json["should_await_complete_spike"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_spike")) {
    this->config.should_await_spike = (bool)api_key_json["should_await_spike"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_enter_as_reversal")) {
    this->config.should_enter_as_reversal =
        (bool)api_key_json["should_enter_as_reversal"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_enter_at_spike")) {
    this->config.should_enter_at_spike =
        (bool)api_key_json["should_enter_at_spike"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_reverse_loss")) {
    this->config.should_reverse_loss =
        (bool)api_key_json["should_reverse_loss"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_reverse_profit")) {
    this->config.should_reverse_profit =
        (bool)api_key_json["should_reverse_profit"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_stop_profit")) {
    this->config.should_stop_profit = (bool)api_key_json["should_stop_profit"];
  }

  // TODO: Decide
  if (api_key_json.contains("spike_duration_minutes")) {
    this->config.spike_duration_minutes =
        (int)api_key_json["spike_duration_minutes"];
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
  if (api_key_json.contains("stop_loss_padding_ratio")) {
    this->config.stop_loss_padding_ratio =
        (double)api_key_json["stop_loss_padding_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_day_range_ratio")) {
    this->config.stop_profit_day_range_ratio =
        (double)api_key_json["stop_profit_day_range_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_ratio")) {
    this->config.stop_profit_ratio = (double)api_key_json["stop_profit_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_target_percentile")) {
    this->config.stop_profit_target_percentile =
        (double)api_key_json["stop_profit_target_percentile"];
  }

  // TODO: Decide
  if (api_key_json.contains("tertiary_reversal_timeframe_minutes")) {
    this->config.tertiary_reversal_timeframe_minutes =
        (int)api_key_json["tertiary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("trend_slip_percentile")) {
    this->config.trend_slip_percentile =
        (double)api_key_json["trend_slip_percentile"];
  }

  this->config = {
      .account_id = api_key_json["id"],
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .authentication_token = api_key_json["authentication_token"],
      .base_url = api_key_json["base_url"],
      .debug_sql = this->config.debug_sql,
      .env_symbols = ::utils::io::read_env_symbols(api_key_json),
      .market_duration_hours =
          this->config.market_duration_hours, // TODO: Decide
      .max_slow_reverse_loss_count =
          this->config.max_slow_reverse_loss_count, // TODO: Decide
      .reversal_proximity_ratio =
          this->config.reversal_proximity_ratio, // TODO: Decide
      .reversal_timeframe_minutes =
          (int)api_key_json["reversal_timeframe_minutes"],
      .secondary_reversal_timeframe_minutes =
          this->config.secondary_reversal_timeframe_minutes, // TODO: Decide
      .should_always_reverse_loss =
          this->config.should_always_reverse_loss, // TODO: Decide
      .should_await_complete_spike =
          this->config.should_await_complete_spike,          // TODO: Decide
      .should_await_spike = this->config.should_await_spike, // TODO: Decide
      .should_enter_as_reversal =
          this->config.should_enter_as_reversal, // TODO: Decide
      .should_enter_at_spike =
          this->config.should_enter_at_spike,                  // TODO: Decide
      .should_reverse_loss = this->config.should_reverse_loss, // TODO: Decide
      .should_reverse_profit =
          this->config.should_reverse_profit,                // TODO: Decide
      .should_stop_profit = this->config.should_stop_profit, // TODO: Decide
      .spike_duration_minutes =
          this->config.spike_duration_minutes,               // TODO: Decide
      .spike_entry_score = this->config.spike_entry_score,   // TODO: Decide
      .spike_height_ratio = this->config.spike_height_ratio, // TODO: Decide
      .stop_loss_padding_ratio =
          this->config.stop_loss_padding_ratio, // TODO: Decide
      .stop_profit_day_range_ratio =
          this->config.stop_profit_day_range_ratio,        // TODO: Decide
      .stop_profit_ratio = this->config.stop_profit_ratio, // TODO: Decide
      .stop_profit_target_percentile =
          this->config.stop_profit_target_percentile, // TODO: Decide
      .tertiary_reversal_timeframe_minutes =
          this->config.tertiary_reversal_timeframe_minutes, // TODO: Decide
      .trend_slip_percentile =
          this->config.trend_slip_percentile, // TODO: Decide
  };
}

#endif
