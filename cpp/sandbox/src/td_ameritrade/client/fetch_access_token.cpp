#if !defined TD_AMERITRADE__CLIENT_fetch_access_token
#define TD_AMERITRADE__CLIENT_fetch_access_token

#include "client.h" // TdAmeritrade::Client, client_config, stream_format
#include "fetch_tokens.cpp"  // fetch_tokens
#include "lib/utils/uri.cpp" // utils::uri
#include <iostream>          // std::cin, std::cout, std::endl
#include <sstream>           // std::stringstream
#include <string>            // std::string

void TdAmeritrade::Client::fetch_access_token() {
  std::string code;
  std::stringstream url;

  url << "https://auth.tdameritrade.com/auth?response_type=code"
      << "&redirect_uri="
      << utils::uri::percent_encode(client_config.redirect_uri)
      << "&client_id=" << client_config.client_id << "%40AMER.OAUTHAP";

  std::cout << stream_format.bold << stream_format.cyan
            << "Your authorization URL: " << stream_format.reset << url.str()
            << std::endl;

  std::cout << stream_format.bold << stream_format.yellow
            << "\nEnter the response code: " << stream_format.reset;

  std::cin >> code;
  std::cout << std::endl;

  fetch_tokens({
      {"code", utils::uri::percent_decode(code)},
      {"grant_type", "authorization_code"},
  });
}
#endif
