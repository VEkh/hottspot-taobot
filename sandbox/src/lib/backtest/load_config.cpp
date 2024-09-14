#ifndef BACKTEST_load_config
#define BACKTEST_load_config

#include "backtest.h"        // Alpaca::TaoBotBacktest, quote_t
#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted::error_message
#include <fstream>           // std::ifstream, std::ios
#include <list>              // std::list
#include <stdexcept>         // std::invalid_argument
#include <stdio.h>           // printf
#include <string>            // std::string
#include <time.h>            // time

void Backtest::load_config() {
  std::string error_message;

  std::ifstream config_file(this->config_path.c_str(), std::ios::in);

  if (!config_file.good()) {
    error_message = Formatted::error_message("Config file missing at " +
                                             std::string(this->config_path));
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
        std::string(this->config_path));

    throw std::invalid_argument(error_message);
  }

  json api_key_json = config_json[api_key];

  if (!api_key_json.contains("backtest")) {
    return;
  }

  json backtest_json = api_key_json["backtest"];

  this->is_active =
      backtest_json.contains("is_active") && (bool)backtest_json["is_active"];

  if (!this->is_active) {
    return;
  }

  std::list<std::string> nested_required_keys = {
      "account_margin_multiplier",
      "account_starting_equity",
      "is_active",
      "start_at",
  };

  for (const std::string key : nested_required_keys) {
    if (backtest_json.contains(key)) {
      continue;
    }

    error_message = Formatted::error_message(
        "Config file is missing the `" + api_key + std::string(".backtest.") +
        std::string(key) + "` key. Please ensure it is in the config file at " +
        std::string(this->config_path));

    throw std::invalid_argument(error_message);
  }

  const std::string start_at_string = backtest_json["start_at"];

  const double start_epoch =
      this->db_utils.timestamp_to_epoch(start_at_string, "America/Chicago");

  double end_epoch;

  if (backtest_json.contains("end_at")) {
    const std::string end_at_string = backtest_json["end_at"];

    end_epoch =
        this->db_utils.timestamp_to_epoch(end_at_string, "America/Chicago");

  } else {
    const std::list<quote_t> last_quotes = this->db_quote.get_last({
        .end_at = (double)time(nullptr),
        .limit = 1,
        .limit_offset = 0,
        .symbol = this->symbol,
    });

    if (last_quotes.empty()) {
      const std::string error_message = Formatted::error_message(
          "No available quotes for " + this->symbol + " in the database.");

      printf("%s\n", error_message.c_str());

      return load_config();
    }

    end_epoch = last_quotes.front().timestamp;
  }

  if (backtest_json.contains("force_exec_slow_queries")) {
    this->config.force_exec_slow_queries =
        (bool)backtest_json["force_exec_slow_queries"];
  }

  this->config = {
      .account_margin_multiplier = backtest_json["account_margin_multiplier"],
      .account_starting_equity = backtest_json["account_starting_equity"],
      .api_key = api_key,
      .api_key_id = api_key_json["id"],
      .end_epoch = end_epoch,
      .force_exec_slow_queries = this->config.force_exec_slow_queries,
      .start_epoch = start_epoch,
  };
}

#endif
