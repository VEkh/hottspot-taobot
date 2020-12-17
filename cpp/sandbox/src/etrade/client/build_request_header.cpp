#if !defined ETRADE__CLIENT_build_request_header
#define ETRADE__CLIENT_build_request_header

#include "client.h"                             // ETrade::Client, client_config
#include "etrade/oauth_header/oauth_header.cpp" // ETrade::OAuthHeader
#include "lib/utils/map.cpp"                    // utils::map
#include <map>                                  // std::map
#include <string>                               // std::string

std::string ETrade::Client::build_request_header(
    std::string request_url, std::map<std::string, std::string> params) {
  std::map<std::string, std::string> merged_params = utils::map::merge(
      params, {
                  {"oauth_consumer_key", oauth.consumer_key},
                  {"oauth_consumer_secret", oauth.consumer_secret},
              });

  ETrade::OAuthHeader oauth_header = ETrade::OAuthHeader({
      .params = merged_params,
      .request_url = request_url,
  });

  return oauth_header.build();
}
#endif
