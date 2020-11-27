#if !defined TD_AMERITRADE__CLIENT_load_client_config
#define TD_AMERITRADE__CLIENT_load_client_config

#include "build_error_message.cpp" // build_error_message
#include "client.h" // CONFIG_PATH, TdAmeritrade::Client, client_config, json_parser
#include "td_ameritrade/deps.cpp" // simdjson

#include <fstream>   // std::ifstream, std::ios, std::ofstream
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

void TdAmeritrade::Client::load_client_config() {
  std::ifstream config_file(CONFIG_PATH, std::ios::in);

  if (!config_file.good()) {
    std::string error_message = build_error_message("Config file missing at " +
                                                    std::string(CONFIG_PATH));
    throw std::invalid_argument(error_message);
  }

  simdjson::dom::element config_json = json_parser.load(CONFIG_PATH);

  client_config = {
      .client_id = std::string(config_json["client_id"]),
      .redirect_uri = std::string(config_json["redirect_uri"]),
  };
}

#endif
