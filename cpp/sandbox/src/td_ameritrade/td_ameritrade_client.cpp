#include "td_ameritrade_client.h" // TOKENS_PATH, json_parser
#include "curl_client.cpp"        // CurlClient
#include "utils/debugger.cpp"     // utils::debugger::inspect
#include <fstream>  // std::ios::out, std::ios::trunc, std::ofstream
#include <iostream> // std::cout
#include <string>   // std::string

// TODO
void TdAmeritradeClient::get_acces_token() {
  std::stringstream url;
  url << "https://auth.tdameritrade.com/auth?response_type=code"
      << "&redirect_uri="
      << "&client_id="
      << "%40AMER.OAUTHAP";

  utils::debugger::inspect(url.str());

  const char *code = "";

  utils::debugger::inspect(utils::uri::percentDecode(code));
}

void TdAmeritradeClient::get_quote(std::string symbol) {
  simdjson::dom::element tokens = json_parser.load("./tmp/td_auth/tokens.json");
  std::string access_token = std::string(tokens["access_token"]);

  CurlClient::props_t props = {
      .body_params = {},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers =
          {
              {"Authorization", "Bearer " + access_token},
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
  curl_client.print_request();
  curl_client.request();
}

void TdAmeritradeClient::refresh_token() {
  simdjson::dom::element client_config =
      json_parser.load("./config/td_ameritrade/credentials.json");

  std::string client_id = std::string(client_config["client_id"]);
  std::string redirect_uri = std::string(client_config["redirect_uri"]);

  simdjson::dom::element tokens = json_parser.load(TOKENS_PATH);
  std::string refresh_token = std::string(tokens["refresh_token"]);

  CurlClient::props_t props = {
      .body_params = {{"access_type", "offline"},
                      {"client_id", client_id},
                      {"grant_type", "refresh_token"},
                      {"redirect_uri", redirect_uri},
                      {"refresh_token", refresh_token}},
      .debug_flag = CurlClient::debug_t::OFF,
      .headers = {{"Content-Type", "application/x-www-form-urlencoded"}},
      .method = CurlClient::http_method_t::POST,
      .query_params = {},
      .url = "https://api.tdameritrade.com/v1/oauth2/token",
  };

  CurlClient curl_client(props);
  curl_client.request();

  simdjson::dom::element response =
      json_parser.parse(curl_client.response.body);

  if (!std::string(response["error"]).empty()) {
    std::cout << response << std::endl;
    return;
  }

  std::cout << "Successfully refreshed tokens: \n"
            << curl_client.response.body << std::endl;

  std::cout << "Writing to: " << TOKENS_PATH << std::endl;

  write_response_to_file(curl_client.response.body, TOKENS_PATH);
}

void TdAmeritradeClient::write_response_to_file(std::string body,
                                                const char *file_path) {
  std::ofstream output_file(file_path, std::ios::out | std::ios::trunc);
  output_file << body;
  output_file.close();
}
