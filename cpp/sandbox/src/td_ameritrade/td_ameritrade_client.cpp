#include "./td_ameritrade_client.h"
#include "../utils/debugger.cpp" // utils::debugger::inspect
#include "./curl_builder.cpp"    // CurlBuilder
#include <string>                // std::string

void TdAmeritradeClient::get_quote(std::string symbol) {
  CurlBuilder::props_t props = {
      .method = "GET",
      .url = "https://api.tdameritrade.com/v1/marketdata/" + symbol + "/quotes",
  };

  simdjson::dom::element tokens = json_parser.load("./tmp/td_auth/tokens.json");
  std::string access_token = std::string(tokens["access_token"]);

  props.headers = {
      {"Authorization", "Bearer " + access_token},
      {"Content-Type", "application/json"},
  };

  props.query_params = {
      {"frequency", "1"},
      {"frequencyType", "daily"},
      {"period", "1"},
      {"periodType", "month"},
  };

  CurlBuilder curl_builder(props);
  std::string request = curl_builder.build();

  utils::debugger::inspect(request);
}

void TdAmeritradeClient::refresh_token() {
  CurlBuilder::props_t props = {
      .method = "POST",
      .url = "https://api.tdameritrade.com/v1/oauth2/token",
  };

  props.headers = {{"Content-Type", "application/x-www-form-urlencoded"}};

  simdjson::dom::element client_config =
      json_parser.load("./tmp/td_auth/credentials.json");

  std::string client_id = std::string(client_config["client_id"]);
  std::string redirect_uri = std::string(client_config["redirect_uri"]);

  simdjson::dom::element tokens = json_parser.load("./tmp/td_auth/tokens.json");
  std::string refresh_token = std::string(tokens["refresh_token"]);

  props.body_params = {{"access_type", "offline"},
                       {"client_id", client_id},
                       {"grant_type", "refresh_token"},
                       {"redirect_uri", redirect_uri},
                       {"refresh_token", refresh_token}};

  CurlBuilder curl_builder(props);
  std::string request = curl_builder.build();

  utils::debugger::inspect(request);
}
