#ifndef ALPACA__TAO_BOT_BACKTEST_load_config
#define ALPACA__TAO_BOT_BACKTEST_load_config

#include "backtest.h"         // Alpaca::TaoBotBacktest, quote_t
#include "deps.cpp"           // json
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/time.cpp" // ::utils::time_
#include <fstream>            // std::ifstream, std::ios
#include <stdexcept>          // std::invalid_argument, std::runtime_error
#include <string>             // std::string
#include <time.h>             // mktime, time, tm
#include <vector>             // std::vector

void Alpaca::TaoBotBacktest::load_config() {
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

  this->is_active = config_json[api_key].contains("is_backtest") &&
                    config_json[api_key]["is_backtest"];

  if (!this->is_active) {
    return;
  }

  std::vector<std::string> nested_required_keys = {
      "backtest_account_margin_multiplier",
      "backtest_account_starting_equity",
      "backtest_start_at",
      "is_backtest",
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

  const std::string start_at_string = config_json[api_key]["backtest_start_at"];

  tm backtest_start_at =
      ::utils::time_::parse_timestamp(start_at_string, "%Y-%m-%d %H:%M:%S");

  const double current_epoch = (double)mktime(&backtest_start_at);

  const std::vector<quote_t> last_quotes = this->db_quote.get_last({
      .limit = 1,
      .symbol = this->symbol,
      .timestamp_upper_bound = (double)time(nullptr),
  });

  if (last_quotes.empty()) {
    const std::string error_message = Formatted::error_message(
        "No available quotes for " + this->symbol + " in the database.");
    throw std::runtime_error(error_message);
  }

  const double end_epoch = last_quotes.front().timestamp;

  this->config = {
      .account_margin_multiplier =
          config_json[api_key]["backtest_account_margin_multiplier"],
      .account_starting_equity =
          config_json[api_key]["backtest_account_starting_equity"],
      .api_key = api_key,
      .api_key_id = config_json[api_key]["id"],
      .end_epoch = end_epoch,
      .start_epoch = current_epoch,
  };
}

#endif
