#if !defined ETRADE__CLIENT_H
#define ETRADE__CLIENT_H

#include "etrade/deps.cpp"                    // json
#include "etrade/oauth_header/oauth_header.h" // ETrade::OAuthHeader
#include "lib/curl_client/curl_client.h"      // CurlClient
#include "lib/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <map>               // std::map
#include <string>            // std::string

namespace ETrade {
class Client {
public:
  enum debug_t { OFF, ON };

  enum order_action_t {
    BUY,
    BUY_TO_COVER,
    SELL,
    SELL_SHORT,
  };

  enum order_status_t {
    ORDER_CANCELLED,
    ORDER_CANCEL_REQUESTED,
    ORDER_EXECUTED,
    ORDER_OPEN,
    ORDER_PARTIAL,
    ORDER_PENDING,
  };

  enum order_type_t {
    LIMIT,
    MARKET,
    STOP_LIMIT,
  };

  struct client_config_t {
    std::string account_id;
    std::string account_id_key;
    std::string base_url;
    std::map<const char *, std::string> paths;
  } client_config;

  struct order_t {
    order_action_t action;
    double execution_price = 0.00;
    int id = 0;
    double limit_price = 0.00;
    double profit = 0.00;
    int quantity;
    double sma_execution_price = 0.00;
    double sma_profit = 0.00;
    double sma_stop_price = 0.00;
    order_status_t status = order_status_t::ORDER_PENDING;
    double stop_price = 0.00;
    const char *symbol;
    order_type_t type;
  };

  struct post_params_t {
    std::string body;
    CurlClient::http_method_t method = CurlClient::http_method_t::POST;
    std::string url;
  };

  struct props_t {
    debug_t debug_flag;
  };

  static constexpr const char *ORDER_STATUSES[6] = {
      "CANCELLED", "CANCEL_REQUESTED", "EXECUTED", "OPEN", "PARTIAL", "PENDING",
  };

  static constexpr const char *ORDER_ACTIONS[4] = {
      "BUY",
      "BUY_TO_COVER",
      "SELL",
      "SELL_SHORT",
  };

  static order_action_t to_order_action_t(const char *);

  CurlClient cancel_order(int);
  CurlClient cancel_order(order_t *);
  CurlClient fetch(char *);
  CurlClient fetch(std::string);
  CurlClient fetch(std::string, std::map<std::string, std::string>);
  CurlClient place_order(order_t *);
  CurlClient preview_order(const order_t &);

  json summarize_quote(const std::string &);

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

  const char *ORDER_TYPES[3] = {
      "LIMIT",
      "MARKET",
      "STOP_LIMIT",
  };

  props_t props = {
      .debug_flag = debug_t::OFF,
  };

  CurlClient handle_place_order_error(const CurlClient &,
                                      const order_action_t &,
                                      const std::string &);
  CurlClient post(post_params_t);

  std::string get_config_filepath(const char *);

  std::string build_place_order_payload(std::string &);
  std::string build_preview_order_payload(const order_t &);
  std::string build_request_header(OAuthHeader::props_t);
  std::string compute_client_order_id(const std::string);
  std::string fetch_token(std::string);

  void fetch_request_token();
  void load_client_config();
  void load_token();
  void write_token(std::string);
};
} // namespace ETrade

#endif
