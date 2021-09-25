#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "types.cpp"                       // Global::t
#include <string>                          // std::string

namespace Oanda {
class Client {
public:
  using quote_t = Global::t::quote_t;

  Client();

  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);

  quote_t parse_quote(const std::string &);

private:
  struct config_t {
    std::string account_id;
    std::string authentication_token;
    std::string base_url;
  } config;

  CurlClient fetch(std::string);

  void load_config();
};
} // namespace Oanda

#endif
