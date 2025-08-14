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
  if (api_key_json.contains("margin_normalization_base_price_action")) {
    this->config.margin_normalization_base_price_action =
        (double)api_key_json["margin_normalization_base_price_action"];
  }

  if (api_key_json.contains("margin_multiplier")) {
    this->config.margin_multiplier = (double)api_key_json["margin_multiplier"];
  }

  if (api_key_json.contains("market_duration_hours")) {
    this->config.market_duration_hours =
        (double)api_key_json["market_duration_hours"];
  }

  if (api_key_json.contains("market_open_central_time")) {
    this->config.market_open_central_time =
        (std::string)api_key_json["market_open_central_time"];
  }

  // TODO: Decide
  if (api_key_json.contains("normalized_account_loss_ratio")) {
    this->config.normalized_account_loss_ratio =
        (double)api_key_json["normalized_account_loss_ratio"];
  }

  if (api_key_json.contains("should_await_record_break")) {
    this->config.should_await_record_break =
        (bool)api_key_json["should_await_record_break"];
  }

  if (api_key_json.contains("should_enter_at_spike")) {
    this->config.should_enter_at_spike =
        (bool)api_key_json["should_enter_at_spike"];
  }

  if (api_key_json.contains("stop_loss_padding_ratio")) {
    this->config.stop_loss_padding_ratio =
        (double)api_key_json["stop_loss_padding_ratio"];
  }

  if (api_key_json.contains("stop_profit_target_price_action")) {
    this->config.stop_profit_target_price_action =
        (double)api_key_json["stop_profit_target_price_action"];
  }

  if (api_key_json.contains("trade_setup_ml_mode")) {
    this->config.trade_setup_ml_mode =
        (std::string)api_key_json["trade_setup_ml_mode"];
  }

  if (api_key_json.contains("trade_setup_reverse_percentile_id")) {
    this->config.trade_setup_reverse_percentile_id =
        (int)api_key_json["trade_setup_reverse_percentile_id"];
  }

  if (api_key_json.contains("trade_setup_stop_profit_id")) {
    this->config.trade_setup_stop_profit_id =
        (int)api_key_json["trade_setup_stop_profit_id"];
  }

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
      .margin_multiplier = this->config.margin_multiplier,
      .margin_normalization_base_price_action =
          this->config.margin_normalization_base_price_action, // TODO: Decide
      .market_duration_hours = this->config.market_duration_hours,
      .market_open_central_time = this->config.market_open_central_time,
      .normalized_account_loss_ratio =
          this->config.normalized_account_loss_ratio, // TODO: Decide
      .should_await_record_break = this->config.should_await_record_break,
      .should_enter_at_spike = this->config.should_enter_at_spike,
      .stop_loss_padding_ratio = this->config.stop_loss_padding_ratio,
      .stop_profit_target_price_action =
          this->config.stop_profit_target_price_action,
      .trade_setup_ml_mode = this->config.trade_setup_ml_mode,
      .trade_setup_reverse_percentile_id =
          this->config.trade_setup_reverse_percentile_id,
      .trade_setup_stop_profit_id = this->config.trade_setup_stop_profit_id,
      .warm_up_period_hours = this->config.warm_up_period_hours,
  };
}

#endif
