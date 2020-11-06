#include "td_ameritrade_client.h"
#include "curl_client.cpp"    // CurlClient
#include "utils/debugger.cpp" // utils::debugger::inspect
#include <string>             // std::string

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
      json_parser.load("./tmp/td_auth/credentials.json");

  std::string client_id = std::string(client_config["client_id"]);
  std::string redirect_uri = std::string(client_config["redirect_uri"]);

  simdjson::dom::element tokens = json_parser.load("./tmp/td_auth/tokens.json");
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
  curl_client.print_request();
  curl_client.request();
  utils::debugger::inspect(curl_client.response.body);
}
