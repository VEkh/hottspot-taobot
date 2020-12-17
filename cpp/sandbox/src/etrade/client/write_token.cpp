#if !defined ETRADE__CLIENT_write_token
#define ETRADE__CLIENT_write_token

#include "client.h"        // ETrade::Client, TOKENS_PATH, props, stream_format
#include "etrade/deps.cpp" // json
#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/io.cpp"     // utils::io
#include "lib/utils/string.cpp" // utils::string
#include "lib/utils/uri.cpp"    // utils::uri
#include <iostream>             // std::cout, std::endl
#include <map>                  // std::map
#include <string>               // std::string

void ETrade::Client::write_token(std::string response_body) {
  Formatted::fmt_stream_t fmt = stream_format;

  if (props.debug_flag == debug_t::ON) {
    std::cout << fmt.bold << fmt.yellow << std::endl;
    std::cout << response_body << std::endl;
    std::cout << "Writing to: " << TOKENS_PATH << std::endl;
    std::cout << fmt.reset;
  }

  std::map<std::string, std::string> parsed_tokens =
      utils::uri::parse_query_params(response_body);

  json tokens_json;
  tokens_json["oauth_token"] =
      utils::string::trim(parsed_tokens["oauth_token"]);
  tokens_json["oauth_token_secret"] =
      utils::string::trim(parsed_tokens["oauth_token_secret"]);

  utils::io::write_to_file(tokens_json.dump(2), TOKENS_PATH);
}

#endif
