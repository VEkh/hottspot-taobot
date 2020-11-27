#if !defined TD_AMERITRADE_CLIENT__GET_ACCESS_TOKEN
#define TD_AMERITRADE_CLIENT__GET_ACCESS_TOKEN

#include "fetch_tokens.cpp" // fetch_tokens
#include "td_ameritrade_client.h" // TdAmeritradeClient, client_config, stream_format
#include "utils/uri.cpp"            // utils::uri
#include <iostream>                 // std::cin, std::cout, std::endl
#include <sstream>                  // std::stringstream
#include <string>                   // std::string

void TdAmeritradeClient::get_access_token() {
  std::string code;
  std::stringstream url;

  url << "https://auth.tdameritrade.com/auth?response_type=code"
      << "&redirect_uri="
      << utils::uri::percentEncode(client_config.redirect_uri)
      << "&client_id=" << client_config.client_id << "%40AMER.OAUTHAP";

  std::cout << stream_format.bold << stream_format.cyan
            << "Your authorization URL: " << stream_format.reset << url.str()
            << std::endl;

  std::cout << stream_format.bold << stream_format.yellow
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
#endif
