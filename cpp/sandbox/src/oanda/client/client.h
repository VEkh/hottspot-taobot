#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "oanda/types.cpp"                 // Oanda::t
#include "types.cpp"                       // Global::t
#include <string>                          // std::string

namespace Oanda {
class Client {
public:
  using order_action_t = Oanda::t::order_action_t;
  using order_t = Oanda::t::order_t;
  using order_status_t = Oanda::t::order_status_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Global::t::quote_t;

  Client();

  CurlClient cancel_order(const int);
  CurlClient cancel_order(order_t *order);
  CurlClient place_order(order_t *order);
  std::string fetch_account();
  std::string fetch_order(const int);
  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);
  std::string fetch_trade(const int);

  quote_t parse_quote(const std::string &);

private:
  struct config_t {
    std::string account_id;
    std::string authentication_token;
    std::string base_url;
  } config;

  CurlClient fetch(std::string);
  CurlClient post(const post_params_t params);

  void load_config();
};
} // namespace Oanda

#endif
