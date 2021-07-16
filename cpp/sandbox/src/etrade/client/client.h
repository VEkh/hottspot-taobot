#ifndef ETRADE__CLIENT_H
#define ETRADE__CLIENT_H

#include "etrade/deps.cpp"                    // json
#include "etrade/oauth_header/oauth_header.h" // ETrade::OAuthHeader
#include "etrade/types.cpp"                   // ETrade::t
#include "lib/curl_client/curl_client.h"      // CurlClient
#include "lib/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <map>               // std::map
#include <string>            // std::string

namespace ETrade {
class Client {
public:
  using order_action_t = ETrade::t::order_action_t;
  using order_status_t = ETrade::t::order_status_t;
  using order_t = ETrade::t::order_t;
  using order_type_t = ETrade::t::order_type_t;
  using quote_t = ETrade::t::quote_t;

  enum debug_t { OFF, ON };

  struct client_config_t {
    std::string account_id;
    std::string account_id_key;
    std::string base_url;
    std::map<const char *, std::string> paths;
  } client_config;

  struct post_params_t {
    std::string body;
    CurlClient::http_method_t method = CurlClient::http_method_t::POST;
    std::string url;
  };

  struct props_t {
    debug_t debug_flag;
  };

  CurlClient cancel_order(int);
  CurlClient cancel_order(order_t *);
  CurlClient fetch(char *);
  CurlClient fetch(std::string);
  CurlClient fetch(std::string, std::map<std::string, std::string>);
  CurlClient place_order(order_t *);
  CurlClient preview_order(const order_t &);

  bool is_next_cycle_retry_error(CurlClient &);

  quote_t parse_quote(const std::string &);

  std::string fetch_account_balance();
  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);

  void fetch_access_token();
  void refresh_token();

  Client();
  Client(props_t);

private:
  struct oauth_params_t {
    std::string consumer_key;
    std::string consumer_secret;
    std::string token;
    std::string token_secret;
    std::string verifier;
  } oauth;

  Formatted::fmt_stream_t stream_format = Formatted::stream();

  props_t props = {
      .debug_flag = debug_t::OFF,
  };

  CurlClient handle_place_order_error(CurlClient &, const order_action_t &,
                                      const std::string &);
  CurlClient post(post_params_t);

  std::string build_place_order_payload(std::string &);
  std::string build_preview_order_payload(const order_t &);
  std::string build_request_header(OAuthHeader::props_t);
  std::string compute_client_order_id(const std::string);
  std::string fetch_token(std::string);
  std::string get_config_filepath(const char *);

  void fetch_request_token();
  void load_client_config();
  void load_token();
  void write_token(std::string);
};
} // namespace ETrade

#endif
