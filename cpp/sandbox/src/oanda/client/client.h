#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
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
  using quote_t = Oanda::t::quote_t;

  Client();

  CurlClient place_order(order_t *order);

  std::string cancel_order(const int);
  std::string cancel_order(order_t *order);
  std::string fetch_account();
  std::string fetch_instrument(const std::string);
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

  Formatted::fmt_stream_t fmt = Formatted::stream();

  CurlClient fetch(std::string);
  CurlClient post(const post_params_t params);

  void load_config();
};
} // namespace Oanda

#endif
