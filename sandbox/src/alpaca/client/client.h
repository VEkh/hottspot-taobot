#ifndef ALPACA__CLIENT_H
#define ALPACA__CLIENT_H

#include "alpaca/types.cpp"                // Alpaca::t
#include "lib/curl_client/curl_client.cpp" // CurlClient
#include "lib/formatted.cpp"               // Formatted
#include "types.cpp"                       // Global::t
#include <map>                             // std::map
#include <string>                          // std::string

namespace Alpaca {
class Client {
public:
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_type_t = Alpaca::t::order_type_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Global::t::quote_t;

  struct config_t {
    double account_stop_loss_ratio = 0.0;
    std::string api_key;
    std::string api_key_id;
    std::string api_secret_key;
    std::string base_url;
    std::string data_base_url;
    bool debug_sql = false;
    bool is_live;
    int late_start_seconds = 6;      // Production's average
    double peak_padding_ratio = 0.0; // TODO: Decide
    int reversal_timeframe_minutes = 3;
    std::string reverse_profit_during = ""; // TODO: Decide
    int secondary_reversal_timeframe_minutes = 0;
    double win_percentile = 0.0; // TODO: Decide
  } config;

  struct fetch_historical_quotes_args_t {
    int batch = 10000;
    double end_at = 0;
    double start_at = 0;
    std::string symbol;
  };

  Client(){};
  Client(std::map<std::string, std::string>);

  CurlClient place_order(order_t *order);

  std::string cancel_order(const std::string &);
  std::string cancel_order(const order_t *order);
  std::string fetch_account();
  std::string fetch_asset(const std::string &);
  std::string fetch_order(const std::string &);
  std::string fetch_quote(char *);
  std::string fetch_quote(const std::string &);
  std::string fetch_historical_quotes(const fetch_historical_quotes_args_t);

  quote_t parse_quote(const std::string &);

  void stream_account();

private:
  struct fetch_params_t {
    std::map<std::string, std::string> query_params;
    int timeout_seconds = 0;
    std::string url;
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::map<std::string, std::string> flags = {
      {"beta", "0"},
      {"paper", "0"},
  };

  CurlClient fetch(const fetch_params_t);
  CurlClient post(const post_params_t);
  void load_config();
};
} // namespace Alpaca

#endif
