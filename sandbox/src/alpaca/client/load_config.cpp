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
      "account_stop_loss_ratio",
      "account_stop_profit_ratio",
      "base_url",
      "is_live",
      "late_start_seconds",
      "secret_key",
      "stop_loss_ratio",
      "stop_profit_ratio",
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

  const double alt_stop_loss_ratio =
      api_key_json.contains("alt_stop_loss_ratio")
          ? (double)api_key_json["alt_stop_loss_ratio"]
          : config.alt_stop_loss_ratio;

  // TODO: Decide
  const int alt_profit_timeout_seconds =
      api_key_json.contains("alt_profit_timeout_seconds")
          ? (int)api_key_json["alt_profit_timeout_seconds"]
          : config.alt_profit_timeout_seconds;

  // TODO: Decide
  const double alt_stop_profit_ratio =
      api_key_json.contains("alt_stop_profit_ratio")
          ? (double)api_key_json["alt_stop_profit_ratio"]
          : config.alt_stop_profit_ratio;

  // TODO: Decide
  const bool is_stop_loss_decayed =
      api_key_json.contains("is_stop_loss_decayed")
          ? (bool)api_key_json["is_stop_loss_decayed"]
          : config.is_stop_loss_decayed;

  const bool is_stop_profit_decayed =
      api_key_json.contains("is_stop_profit_decayed")
          ? (bool)api_key_json["is_stop_profit_decayed"]
          : config.is_stop_profit_decayed;

  // TODO: Decide
  const int profit_timeout_seconds =
      api_key_json.contains("profit_timeout_seconds")
          ? (int)api_key_json["profit_timeout_seconds"]
          : config.profit_timeout_seconds;

  // TODO: Decide
  const bool should_await_reclaimed_profit =
      api_key_json.contains("should_await_reclaimed_profit")
          ? (bool)api_key_json["should_await_reclaimed_profit"]
          : config.should_await_reclaimed_profit;

  // TODO: Decide
  const bool should_expand_stop_loss =
      api_key_json.contains("should_expand_stop_loss")
          ? (bool)api_key_json["should_expand_stop_loss"]
          : config.should_expand_stop_loss;

  // TODO: Decide
  const bool should_toggle_profit_timeout_seconds =
      api_key_json.contains("should_toggle_profit_timeout_seconds")
          ? (bool)api_key_json["should_toggle_profit_timeout_seconds"]
          : config.should_toggle_profit_timeout_seconds;

  // TODO: Decide
  const bool should_toggle_stop_loss =
      api_key_json.contains("should_toggle_stop_loss")
          ? (bool)api_key_json["should_toggle_stop_loss"]
          : config.should_toggle_stop_loss;

  // TODO: Decide
  const bool should_toggle_stop_profit =
      api_key_json.contains("should_toggle_stop_profit")
          ? (bool)api_key_json["should_toggle_stop_profit"]
          : config.should_toggle_stop_profit;

  // TODO: Decide
  const bool should_toggle_stop_profit_decay =
      api_key_json.contains("should_toggle_stop_profit_decay")
          ? (bool)api_key_json["should_toggle_stop_profit_decay"]
          : config.should_toggle_stop_profit_decay;

  // TODO: Decide
  const bool should_use_alt_profit_timeout_seconds =
      api_key_json.contains("should_use_alt_profit_timeout_seconds")
          ? (bool)api_key_json["should_use_alt_profit_timeout_seconds"]
          : config.should_use_alt_profit_timeout_seconds;

  // TODO: Decide
  const bool should_use_alt_stop_profit =
      api_key_json.contains("should_use_alt_stop_profit")
          ? (bool)api_key_json["should_use_alt_stop_profit"]
          : config.should_use_alt_stop_profit;

  const bool should_use_alt_stop_loss =
      api_key_json.contains("should_use_alt_stop_loss")
          ? (bool)api_key_json["should_use_alt_stop_loss"]
          : config.should_use_alt_stop_loss;

  std::map<std::string, double> stop_loss_ratios =
      api_key_json.contains("stop_loss_ratios")
          ? (std::map<std::string, double>)api_key_json["stop_loss_ratios"]
          : config.stop_loss_ratios;

  std::map<std::string, double> stop_profit_ratios =
      api_key_json.contains("stop_profit_ratios")
          ? (std::map<std::string, double>)api_key_json["stop_profit_ratios"]
          : config.stop_profit_ratios;

  const int terminate_after_seconds =
      api_key_json.contains("terminate_after_seconds")
          ? (int)api_key_json["terminate_after_seconds"]
          : config.terminate_after_seconds;

  ml_config_t ml_config;

  if (api_key_json.contains("ml")) {
    json ml_json = api_key_json["ml"];

    if (ml_json.contains("candle_predict")) {
      json candle_predict_json = ml_json["candle_predict"];

      ml_config.candle_predict.duration_minutes =
          candle_predict_json.contains("duration_minutes")
              ? (int)candle_predict_json["duration_minutes"]
              : ml_config.candle_predict.duration_minutes;

      ml_config.candle_predict.enabled =
          candle_predict_json.contains("enabled")
              ? (bool)candle_predict_json["enabled"]
              : ml_config.candle_predict.enabled;

      ml_config.candle_predict.hold_winning_prediction =
          candle_predict_json.contains("hold_winning_prediction")
              ? (bool)candle_predict_json["hold_winning_prediction"]
              : ml_config.candle_predict.hold_winning_prediction;

      ml_config.candle_predict.inverse_predictions =
          candle_predict_json.contains("inverse_predictions")
              ? (bool)candle_predict_json["inverse_predictions"]
              : ml_config.candle_predict.inverse_predictions;

      ml_config.candle_predict.on_demand_predictions =
          candle_predict_json.contains("on_demand_predictions")
              ? (bool)candle_predict_json["on_demand_predictions"]
              : ml_config.candle_predict.on_demand_predictions;

      ml_config.candle_predict.prediction_scope =
          candle_predict_json.contains("prediction_scope")
              ? (std::string)candle_predict_json["prediction_scope"]
              : ml_config.candle_predict.prediction_scope;

      ml_config.candle_predict.rollover_positions =
          candle_predict_json.contains("rollover_positions")
              ? (bool)candle_predict_json["rollover_positions"]
              : ml_config.candle_predict.rollover_positions;

      ml_config.candle_predict.symbol_model_map =
          candle_predict_json.contains("symbol_model_map")
              ? (std::map<std::string, std::string>)
                    candle_predict_json["symbol_model_map"]
              : ml_config.candle_predict.symbol_model_map;
    }
  }

  this->config = {
      .account_stop_loss_ratio = api_key_json["account_stop_loss_ratio"],
      .account_stop_profit_ratio = api_key_json["account_stop_profit_ratio"],
      .alt_profit_timeout_seconds = alt_profit_timeout_seconds, // TODO: Decide
      .alt_stop_loss_ratio = alt_stop_loss_ratio,
      .alt_stop_profit_ratio = alt_stop_profit_ratio, // TODO: Decide
      .api_key = api_key,
      .api_key_id = api_key_json["id"],
      .api_secret_key = api_key_json["secret_key"],
      .base_url = api_key_json["base_url"],
      .data_base_url = config_json["data_base_url"],
      .is_live = api_key_json["is_live"],
      .is_stop_loss_decayed = is_stop_loss_decayed, // TODO: Decide
      .is_stop_profit_decayed = is_stop_profit_decayed,
      .late_start_seconds = api_key_json["late_start_seconds"],
      .ml = ml_config,
      .profit_timeout_seconds = profit_timeout_seconds, // TODO: Decide
      .should_await_reclaimed_profit =
          should_await_reclaimed_profit,                  // TODO: Decide
      .should_expand_stop_loss = should_expand_stop_loss, // TODO: Decide
      .should_toggle_profit_timeout_seconds =
          should_toggle_profit_timeout_seconds,               // TODO: Decide
      .should_toggle_stop_loss = should_toggle_stop_loss,     // TODO: Decide
      .should_toggle_stop_profit = should_toggle_stop_profit, // TODO: Decide
      .should_toggle_stop_profit_decay =
          should_toggle_stop_profit_decay, // TODO: Decide
      .should_use_alt_profit_timeout_seconds =
          should_use_alt_profit_timeout_seconds, // TODO: Decide
      .should_use_alt_stop_loss = should_use_alt_stop_loss,
      .should_use_alt_stop_profit = should_use_alt_stop_profit, // TODO: Decide
      .stop_loss_ratio = api_key_json["stop_loss_ratio"],
      .stop_loss_ratios = stop_loss_ratios,
      .stop_profit_ratio = api_key_json["stop_profit_ratio"],
      .stop_profit_ratios = stop_profit_ratios,
      .terminate_after_seconds = terminate_after_seconds,
  };
}

#endif
