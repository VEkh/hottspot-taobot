#ifndef ETRADE__CLIENT_fetch_access_token
#define ETRADE__CLIENT_fetch_access_token

#include "client.h" // ETrade::Client, config, stream_format
#include "fetch_request_token.cpp" // fetch_request_token
#include "fetch_token.cpp"         // fetch_token
#include "lib/formatted.cpp"       // Formatted
#include "lib/utils/io.cpp"        // utils::io
#include "write_token.cpp"         // write_token
#include <iostream>                // std::cin, std::cout, std::endl
#include <map>                     // std::map
#include <sstream>                 // std::stringstream
#include <stdexcept>               // std::runtime_error
#include <stdio.h>                 // printf, puts
#include <string>                  // std::string

void ETrade::Client::fetch_access_token() {
  Formatted::fmt_stream_t fmt = stream_format;
  std::stringstream url;

  fetch_request_token();

  url << "https://us.etrade.com/e/t/etws/authorize?"
      << "key=" << this->oauth.consumer_key << "&token=" << this->oauth.token;

  std::stringstream cmd;
  cmd << "GEM_HOME=" << RUBYGEMS_DIR << " " << RUBY_PATH << " " << APP_DIR
      << "/src/etrade/fetch_access_token.rb \"" << url.str() << "\"";

  std::cout << fmt.bold << fmt.cyan << std::endl;
  puts("Fetching verifier with Selenium.\n");
  std::cout << fmt.reset;

  const std::string verifier = ::utils::io::system_exec(cmd.str());

  if (verifier.size() != 5) {
    std::string error_message =
        Formatted::error_message("Failed to fetch the verifier with error.");

    throw(std::runtime_error(error_message));
  }

  oauth.verifier = verifier;

  std::string token_response =
      fetch_token(config.base_url + "/oauth/access_token");

  write_token(token_response);
}

#endif
