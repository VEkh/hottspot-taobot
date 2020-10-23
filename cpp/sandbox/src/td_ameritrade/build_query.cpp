#include "../utils/debugger.cpp" // utils::debugger::inspect
#include "../utils/uri.cpp"      // utils::uri::percentEncode
#include "./curl_builder.cpp"    // CurlBuilder
#include <map>                   // std::map
#include <string>                // std::string

// Auth Params
// CurlBuilder::props_t build_props() {
//   CurlBuilder::props_t props = {
//       .method = "POST",
//       .url = "https://api.tdameritrade.com/v1/oauth2/token",
//   };

//   props.headers = {{"Content-Type", "application/x-www-form-urlencoded"}};

//   props.body_params = {
//       {"access_type", "offline"},
//       {"client_id", ""},
//       {"grant_type", "refresh_token"},
//       {"redirect_uri", "https://127.0.0.1"},
//       {"refresh_token", ""},
//   };

//   return props;
// }

CurlBuilder::props_t build_props() {
  CurlBuilder::props_t props = {
      .method = "GET",
      .url = "https://api.tdameritrade.com/v1/marketdata/GOOG/pricehistory",
  };

  props.headers = {
      {"Authorization", "Bearer "},
      {"Content-Type", "application/json"},
  };

  props.query_params = {
      {"frequency", "1"},
      {"frequencyType", "daily"},
      {"period", "1"},
      {"periodType", "month"},
  };

  return props;
}

int main() {
  CurlBuilder curl_builder(build_props());
  std::string curl_request = curl_builder.build();

  utils::debugger::inspect(curl_request);
}
