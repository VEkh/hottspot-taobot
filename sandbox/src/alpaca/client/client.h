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
  using ml_config_t = Global::t::ml_config_t;
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_type_t = Alpaca::t::order_type_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Global::t::quote_t;

  struct config_t {
    double account_stop_loss_ratio = 0.0;
    double account_stop_profit_ratio = 0.0;
    int alt_profit_timeout_seconds = 0; // TODO: Decide
    double alt_stop_loss_ratio = 0.0;
    double alt_stop_profit_ratio = 0.0; // TODO: Decide
    std::string api_key;
    std::string api_key_id;
    std::string api_secret_key;
    std::string base_url;
    int candles_timeframe_minutes = 0; // TODO: Decide
    std::string data_base_url;
    double deficit_reclaim_ratio = 0.0; // TODO: Decide
    bool is_live;
    bool is_stop_loss_dynamic = false; // TODO: Decide
    int late_start_seconds = 6;        // Production's average
    ml_config_t ml;
    double profit_reclaim_ratio = 0.0;            // TODO: Decide
    int profit_timeout_seconds = 0;               // TODO: Decide
    int reversal_timeframe_minutes = 5;           // TODO: Decide
    int secondary_reversal_timeframe_minutes = 0; // TODO: Decide
    bool should_await_reversal_indicator = false; // TODO: Decide
    bool should_reverse_losses = false;           // TODO: Decide
    bool should_ride_trans_reversals = false;     // TODO: Decide
    double stop_loss_percent = -0.0;
    double stop_loss_ratio = -60.0;
    std::map<std::string, double> stop_loss_ratios;
    double stop_profit_max_ratio = 0.0; // TODO: Decide
    double stop_profit_ratio = 0.0;
    double stop_profit_trend_ratio = 0.0; // TODO: Decide
    std::map<std::string, double> stop_profit_ratios;
    int terminate_after_seconds = 0;
    int toggle_is_trending_after_n = 0; // TODO: Decide
  } config;

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

  quote_t parse_quote(const std::string &);

  void stream_account();

private:
  struct fetch_params_t {
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
