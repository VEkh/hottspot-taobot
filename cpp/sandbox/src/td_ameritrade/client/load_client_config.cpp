#if !defined TD_AMERITRADE__CLIENT_load_client_config
#define TD_AMERITRADE__CLIENT_load_client_config

#include "client.h" // CONFIG_PATH, TdAmeritrade::Client, client_config, json_parser
#include "lib/formatted.cpp"      // Formatted::error_message
#include "td_ameritrade/deps.cpp" // json

#include <fstream>   // std::ifstream, std::ios, std::ofstream
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

void TdAmeritrade::Client::load_client_config() {
  std::ifstream config_file(CONFIG_PATH, std::ios::in);

  if (!config_file.good()) {
    std::string error_message = Formatted::error_message(
        "Config file missing at " + std::string(CONFIG_PATH));
    throw std::invalid_argument(error_message);
  }

  json config_json;
  config_file >> config_json;

  client_config = {
      .client_id = std::string(config_json["client_id"]),
      .redirect_uri = std::string(config_json["redirect_uri"]),
  };
}

#endif
