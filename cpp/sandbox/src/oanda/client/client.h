#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "deps.cpp"                        // json
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "oanda/types.cpp"                 // Oanda::t
#include "types.cpp"                       // Global::t
#include <map>                             // std::map
#include <string>                          // std::string
#include <vector>                          // std::vector

namespace Oanda {
class Client {
public:
  using order_action_t = Oanda::t::order_action_t;
  using order_t = Oanda::t::order_t;
  using order_status_t = Oanda::t::order_status_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Oanda::t::quote_t;

  Client(std::map<std::string, std::string> = {});

  CurlClient place_order(order_t *order);

  std::map<std::string, std::string> map_margin_rates(json);
  std::string cancel_order(const int);
  std::string cancel_order(order_t *order);
  std::string fetch_account();
  std::string fetch_instruments(const std::vector<std::string>);
  std::string fetch_order(const int);
  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);
  std::string fetch_trade(const int);

  quote_t parse_quote(const std::string &);

  void stream_account();

private:
  struct config_t {
    std::string account_id;
    std::string authentication_token;
    std::string base_url;
  } config;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::map<std::string, std::string> flags = {{"paper", "0"}};

  CurlClient fetch(std::string);
  CurlClient post(const post_params_t params);
  bool is_live();
  void load_config();
};
} // namespace Oanda

#endif
