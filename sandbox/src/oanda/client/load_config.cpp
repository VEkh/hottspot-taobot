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
  if (api_key_json.contains("margin_multiplier")) {
    this->config.margin_multiplier = (double)api_key_json["margin_multiplier"];
  }

  // TODO: Decide
  if (api_key_json.contains("post_win_reverse_profit_percentile")) {
    this->config.post_win_reverse_profit_percentile =
        (double)api_key_json["post_win_reverse_profit_percentile"];
  }

  // TODO: Decide
  if (api_key_json.contains("range_min_height")) {
    this->config.range_min_height = (double)api_key_json["range_min_height"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_always_reverse_profit")) {
    this->config.should_always_reverse_profit =
        (bool)api_key_json["should_always_reverse_profit"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_await_record_break")) {
    this->config.should_await_record_break =
        (bool)api_key_json["should_await_record_break"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_enter_at_spike")) {
    this->config.should_enter_at_spike =
        (bool)api_key_json["should_enter_at_spike"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_enter_in_trend_direction")) {
    this->config.should_enter_in_trend_direction =
        (bool)api_key_json["should_enter_in_trend_direction"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_only_enter_at_record")) {
    this->config.should_only_enter_at_record =
        (bool)api_key_json["should_only_enter_at_record"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_only_win_once")) {
    this->config.should_only_win_once =
        (bool)api_key_json["should_only_win_once"];
  }

  // TODO: Decide
  if (api_key_json.contains("should_reverse_loss_at_equator")) {
    this->config.should_reverse_loss_at_equator =
        (bool)api_key_json["should_reverse_loss_at_equator"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_loss_padding_ratio")) {
    this->config.stop_loss_padding_ratio =
        (double)api_key_json["stop_loss_padding_ratio"];
  }

  // TODO: Decide
  if (api_key_json.contains("stop_profit_multiplier")) {
    this->config.stop_profit_multiplier =
        (double)api_key_json["stop_profit_multiplier"];
  }

  // TODO: Decide
  if (api_key_json.contains("warm_up_period_hours")) {
    this->config.warm_up_period_hours =
        (double)api_key_json["warm_up_period_hours"];
  }

  this->config = {
      .account_id = api_key_json["id"],
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .authentication_token = api_key_json["authentication_token"],
      .base_url = api_key_json["base_url"],
      .debug_sql = this->config.debug_sql,
      .env_symbols = ::utils::io::read_env_symbols(api_key_json),
      .margin_multiplier = this->config.margin_multiplier, // TODO: Decide
      .post_win_reverse_profit_percentile =
          this->config.post_win_reverse_profit_percentile, // TODO: Decide
      .range_min_height = this->config.range_min_height,   // TODO: Decide
      .should_always_reverse_profit =
          this->config.should_always_reverse_profit, // TODO: Decide
      .should_await_record_break =
          this->config.should_await_record_break, // TODO: Decide
      .should_enter_at_spike =
          this->config.should_enter_at_spike, // TODO: Decide
      .should_enter_in_trend_direction =
          this->config.should_enter_in_trend_direction, // TODO: Decide
      .should_only_enter_at_record =
          this->config.should_only_enter_at_record,              // TODO: Decide
      .should_only_win_once = this->config.should_only_win_once, // TODO: Decide
      .should_reverse_loss_at_equator =
          this->config.should_reverse_loss_at_equator, // TODO: Decide
      .stop_loss_padding_ratio =
          this->config.stop_loss_padding_ratio, // TODO: Decide
      .stop_profit_multiplier =
          this->config.stop_profit_multiplier,                   // TODO: Decide
      .warm_up_period_hours = this->config.warm_up_period_hours, // TODO: Decide
  };
}

#endif
