#if !defined TD_AMERITRADE_CLIENT__LOAD_CLIENT_CONFIG
#define TD_AMERITRADE_CLIENT__LOAD_CLIENT_CONFIG

#if !defined DEPENDENCY_SIMDJSON
#include "deps/simdjson/simdjson.cpp" // simdjson
#endif

#include "build_error_message.cpp" // build_error_message
#include "td_ameritrade_client.h" // CONFIG_PATH, TdAmeritradeClient, client_config, json_parser

#include <fstream>   // std::ifstream, std::ios, std::ofstream
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

void TdAmeritradeClient::load_client_config() {
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
