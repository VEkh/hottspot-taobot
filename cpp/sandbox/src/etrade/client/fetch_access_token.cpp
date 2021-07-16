#ifndef ETRADE__CLIENT_fetch_access_token
#define ETRADE__CLIENT_fetch_access_token

#include "client.h" // ETrade::Client, client_config, stream_format
#include "fetch_request_token.cpp" // fetch_request_token
#include "fetch_token.cpp"         // fetch_token
#include "lib/formatted.cpp"       // Formatted
#include "write_token.cpp"         // write_token
#include <iostream>                // std::cin, std::cout, std::endl
#include <map>                     // std::map
#include <sstream>                 // std::stringstream
#include <string>                  // std::string

void ETrade::Client::fetch_access_token() {
  Formatted::fmt_stream_t fmt = stream_format;
  std::stringstream url;

  fetch_request_token();

  url << "https://us.etrade.com/e/t/etws/authorize?"
      << "key=" << oauth.consumer_key << "&token=" << oauth.token;

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "Your authorization URL: " << fmt.reset << url.str()
            << std::endl;

  std::cout << fmt.bold << fmt.yellow << std::endl;
  std::cout << "Enter the response verifier: ";
  std::cout << fmt.reset;

  std::cin >> oauth.verifier;
  std::cout << std::endl;

  std::string token_response =
      fetch_token(client_config.base_url + "/oauth/access_token");

  write_token(token_response);
}

#endif
