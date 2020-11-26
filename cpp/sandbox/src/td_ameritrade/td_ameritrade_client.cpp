#include "td_ameritrade_client.h" // TOKENS_PATH, json_parser
#include "curl_client.cpp"        // CurlClient
#include "utils/debugger.cpp"     // utils::debugger::inspect
#include "utils/uri.cpp"          // utils::uri::percentEncode
#include <fstream>   // std::ios::out, std::ios::trunc, std::ofstream
#include <iostream>  // std::cin, std::cout, std::endl
#include <sstream>   // std::ostringstream, std::stringstream
#include <stdexcept> // std::invalid_argument
#include <string>    // std::string

TdAmeritradeClient::TdAmeritradeClient() { load_client_config(); }

void TdAmeritradeClient::get_access_token() {
  std::string code;
  std::stringstream url;

  url << "https://auth.tdameritrade.com/auth?response_type=code"
      << "&redirect_uri="
      << utils::uri::percentEncode(client_config.redirect_uri)
      << "&client_id=" << client_config.client_id << "%40AMER.OAUTHAP";

  std::cout << stream_format.cyan
            << "Your authorization URL: " << stream_format.reset << url.str()
            << std::endl;

  std::cout << stream_format.yellow
            << "\nEnter the response code: " << stream_format.reset;

  std::cin >> code;
  std::cout << std::endl;

  fetch_tokens({
      {"access_type", "offline"},
      {"client_id", client_config.client_id},
      {"code", utils::uri::percentDecode(code)},
      {"grant_type", "authorization_code"},
      {"redirect_uri", client_config.redirect_uri},
  });
}

void TdAmeritradeClient::get_quote(std::string symbol) {
  load_tokens();

  CurlClient::props_t props = {
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"Authorization", "Bearer " + tokens.access_token},
              {"Content-Type", "application/json"},
          },
      .method = CurlClient::http_method_t::GET,
      .query_params =
          {
              {"frequency", "1"},
              {"frequencyType", "daily"},
              {"period", "1"},
              {"periodType", "month"},
          },
      .url = "https://api.tdameritrade.com/v1/marketdata/" + symbol + "/quotes",
  };

  CurlClient curl_client(props);
  curl_client.request();

  utils::debugger::inspect(curl_client.response.body);
}

void TdAmeritradeClient::refresh_tokens() {
  load_tokens();

  fetch_tokens({
      {"access_type", "offline"},
      {"client_id", client_config.client_id},
      {"grant_type", "refresh_token"},
      {"redirect_uri", client_config.redirect_uri},
      {"refresh_token", tokens.refresh_token},
  });
}

// private

std::string TdAmeritradeClient::build_error_message(std::string message) {
  std::ostringstream formatted_message;

  formatted_message << stream_format.red << message << stream_format.reset;

  return formatted_message.str();
}

void TdAmeritradeClient::fetch_tokens(
    std::map<std::string, std::string> body_params) {
  CurlClient::props_t curl_props = {
      .body_params = body_params,
      .debug_flag = CurlClient::debug_t::OFF,
      .headers = {{"Content-Type", "application/x-www-form-urlencoded"}},
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = "https://api.tdameritrade.com/v1/oauth2/token",
  };

  CurlClient curl_client(curl_props);
  curl_client.request();

  std::string response_body = curl_client.response.body;
  simdjson::dom::element response = json_parser.parse(response_body);

  simdjson::dom::element error_message;
  auto json_error = response["error"].get(error_message);

  if (!json_error) {
    std::string error_message = build_error_message("Request FAILED");

    utils::debugger::inspect(error_message);
    std::cout << response << std::endl;

    exit(1);
  }

  std::cout << stream_format.green << "Successfully fetched tokens: \n"
            << stream_format.reset << response_body << std::endl;

  std::cout << "Writing to: " << TOKENS_PATH << std::endl;

  write_response_to_file(response_body, TOKENS_PATH);
}

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

void TdAmeritradeClient::load_tokens() {
  std::ifstream tokens_file(TOKENS_PATH, std::ios::in);

  if (!tokens_file.good()) {
    std::string error_message =
        build_error_message("Tokens missing at " + std::string(TOKENS_PATH) +
                            ". Run `TdAmeritradeClient::fetch_tokens` first.");

    throw std::invalid_argument(error_message);
  }

  simdjson::dom::element tokens_json = json_parser.load(TOKENS_PATH);

  tokens = {
      .access_token = std::string(tokens_json["access_token"]),
      .refresh_token = std::string(tokens_json["refresh_token"]),
  };
}

void TdAmeritradeClient::write_response_to_file(std::string body,
                                                const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}
