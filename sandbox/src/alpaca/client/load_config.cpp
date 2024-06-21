#ifndef ALPACA__CLIENT_load_config
#define ALPACA__CLIENT_load_config

#include "client.h"           // Alpaca::Client
#include "deps.cpp"           // json
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/io.cpp"   // ::utils::io
#include "lib/utils/time.cpp" // ::utils::time_
#include <map>                // std::map
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string, std::stod // TODO: Decide
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

  // TODO: Decide
  if (api_key_json.contains("dynamic_trend_type")) {
    config.dynamic_trend_type = (std::string)api_key_json["dynamic_trend_type"];
  }

  if (api_key_json.contains("reversal_timeframe_minutes")) {
    config.reversal_timeframe_minutes =
        (int)api_key_json["reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("non_init_reversing_stop_loss_ratio")) {
    config.non_init_reversing_stop_loss_ratio =
        (double)api_key_json["non_init_reversing_stop_loss_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("non_init_reversing_trailing_stop_loss_ratio")) {
    config.non_init_reversing_trailing_stop_loss_ratio =
        (double)api_key_json["non_init_reversing_trailing_stop_loss_ratio"];
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

  // TODO: Decide
  if (api_key_json.contains("second_reversal_ref_type")) {
    config.second_reversal_ref_type =
        (std::string)api_key_json["second_reversal_ref_type"];
  }

  if (api_key_json.contains("secondary_reversal_timeframe_minutes")) {
    config.secondary_reversal_timeframe_minutes =
        (int)api_key_json["secondary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_after_no_max_loss")) {
    config.should_await_after_no_max_loss =
        (bool)api_key_json["should_await_after_no_max_loss"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_init_trend")) {
    config.should_await_init_trend =
        (bool)api_key_json["should_await_init_trend"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_immediately_reverse_non_init_reversing")) {
    config.should_immediately_reverse_non_init_reversing =
        (bool)api_key_json["should_immediately_reverse_non_init_reversing"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_toggle_dynamic_trend_type")) {
    config.should_toggle_dynamic_trend_type =
        (bool)api_key_json["should_toggle_dynamic_trend_type"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_trend_enter_at_record")) {
    config.should_trend_enter_at_record =
        (bool)api_key_json["should_trend_enter_at_record"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_trend_entry_await_correction")) {
    config.should_trend_entry_await_correction =
        (bool)api_key_json["should_trend_entry_await_correction"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_symbols")) {
    json stop_profit_symbols = api_key_json["stop_profit_symbols"];

    config.stop_profit_symbols =
        (std::map<std::string, bool>)stop_profit_symbols;
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_percentile_tiers")) {
    json stop_profit_percentile_tiers =
        api_key_json["stop_profit_percentile_tiers"];

    std::map<std::string, int> raw =
        (std::map<std::string, int>)stop_profit_percentile_tiers;

    std::map<double, int> formatted;

    std::map<std::string, int>::iterator it;

    for (it = raw.begin(); it != raw.end(); it++) {
      formatted[std::stod(it->first)] = it->second;
    }

    config.stop_profit_percentile_tiers = formatted;
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_tiers")) {
    json stop_profit_tiers = api_key_json["stop_profit_tiers"];

    std::map<std::string, int> raw =
        (std::map<std::string, int>)stop_profit_tiers;

    std::map<double, int> formatted;

    std::map<std::string, int>::iterator it;

    for (it = raw.begin(); it != raw.end(); it++) {
      formatted[std::stod(it->first)] = it->second;
    }

    config.stop_profit_tiers = formatted;
  }

  // TODO: Decide
  if (api_key_json.contains("tertiary_reversal_timeframe_minutes")) {
    config.tertiary_reversal_timeframe_minutes =
        (int)api_key_json["tertiary_reversal_timeframe_minutes"];
  }

  // TODO: Decide
  if (api_key_json.contains("trend_entry_percentile")) {
    config.trend_entry_percentile =
        (double)api_key_json["trend_entry_percentile"];
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

  // TODO: Decide
  if (api_key_json.contains("win_percentile_range")) {
    config.win_percentile_range =
        (std::string)api_key_json["win_percentile_range"];
  }

  this->config = {
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .api_key = api_key,
      .api_key_id = api_key_json["id"],
      .api_secret_key = api_key_json["secret_key"],
      .base_url = api_key_json["base_url"],
      .data_base_url = config_json["data_base_url"],
      .debug_sql = config.debug_sql,
      .dynamic_trend_type = config.dynamic_trend_type, // TODO: Decide
      .is_live = api_key_json["is_live"],
      .late_start_seconds = api_key_json["late_start_seconds"],
      .non_init_reversing_stop_loss_ratio =
          config.non_init_reversing_stop_loss_ratio, // TODO: Decide
      .non_init_reversing_trailing_stop_loss_ratio =
          config.non_init_reversing_trailing_stop_loss_ratio, // TODO: Decide
      .peak_padding_ratio = config.peak_padding_ratio,        // TODO: Decide
      .reversal_timeframe_minutes = config.reversal_timeframe_minutes,
      .reverse_profit_during = config.reverse_profit_during, // TODO: Decide
      .second_reversal_ref_type =
          config.second_reversal_ref_type, // TODO: Decide
      .secondary_reversal_timeframe_minutes =
          config.secondary_reversal_timeframe_minutes,
      .should_await_after_no_max_loss =
          config.should_await_after_no_max_loss,                 // TODO: Decide
      .should_await_init_trend = config.should_await_init_trend, // TODO: Decide
      .should_immediately_reverse_non_init_reversing =
          config.should_immediately_reverse_non_init_reversing, // TODO: Decide
      .should_toggle_dynamic_trend_type =
          config.should_toggle_dynamic_trend_type, // TODO: Decide
      .should_trend_enter_at_record =
          config.should_trend_enter_at_record, // TODO: Decide
      .should_trend_entry_await_correction =
          config.should_trend_entry_await_correction,    // TODO: Decide
      .stop_profit_symbols = config.stop_profit_symbols, // TODO: Decide
      .stop_profit_percentile_tiers =
          config.stop_profit_percentile_tiers,       // TODO: Decide
      .stop_profit_tiers = config.stop_profit_tiers, // TODO: Decide
      .tertiary_reversal_timeframe_minutes =
          config.tertiary_reversal_timeframe_minutes,          // TODO: Decide
      .trend_entry_percentile = config.trend_entry_percentile, // TODO: Decide
      .trend_slip_percentile = config.trend_slip_percentile,   // TODO: Decide
      .win_percentile = config.win_percentile,                 // TODO: Decide
      .win_percentile_range = config.win_percentile_range,     // TODO: Decide
  };
}

#endif
