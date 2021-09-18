#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include <string>                          // std::string

namespace Oanda {
class Client {
public:
  Client();

  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);

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
