#if !defined ETRADE__CLIENT_fetch_access_token
#define ETRADE__CLIENT_fetch_access_token

#include "authorized_fetch_access_token.cpp" // authorized_fetch_access_token
#include "client.h" // ETrade::Client, client_config, stream_format
#include "fetch_request_token.cpp" // fetch_request_token
#include "lib/formatted.cpp"       // Formatted
#include <iostream>                // std::cin, std::cout, std::endl
#include <map>                     // std::map
#include <sstream>                 // std::stringstream
#include <string>                  // std::string

void ETrade::Client::fetch_access_token() {
  Formatted::fmt_stream_t fmt = stream_format;
  std::stringstream url;

  fetch_request_token();

  url << "https://us.etrade.com/e/t/etws/authorize?"
      << "key=" << client_config.oauth_consumer_key
      << "&token=" << client_config.oauth_token;

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << "Your authorization URL: " << fmt.reset << url.str()
            << std::endl;

  std::cout << fmt.bold << fmt.yellow << std::endl;
  std::cout << "Enter the response verifier: ";
  std::cout << fmt.reset;

  std::cin >> client_config.oauth_verifier;
  std::cout << std::endl;

  authorized_fetch_access_token();
}

#endif
