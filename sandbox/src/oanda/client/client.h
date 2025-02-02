#ifndef OANDA__CLIENT_H
#define OANDA__CLIENT_H

#include "db/historical_quote/base/base.cpp" // DB::HistoricalQuote::Base
#include "deps.cpp"                          // json
#include "lib/curl_client/curl_client.cpp"   // CurlClient
#include "lib/formatted.cpp"                 // Formatted
#include "oanda/types.cpp"                   // Oanda::t
#include "types.cpp"                         // Global::t
#include <list>                              // std::list
#include <map>                               // std::map
#include <string>                            // std::string
#include <vector>                            // std::vector

namespace Oanda {
class Client {
public:
  using order_action_t = Oanda::t::order_action_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Global::t::quote_t;

  struct config_t {
    std::string account_id;
    double account_stop_loss_ratio = 0.0;
    std::string authentication_token;
    std::string base_url;
    bool debug_sql = false;
    std::list<std::string> env_symbols;
    double margin_throttle = 1.0;         // TODO: Decide
    int reversal_timeframe_minutes = 120; // TODO: Decide
    bool should_stop_profit_once = false; // TODO: Decide
    double spike_entry_score = 5.0;       // TODO: Decide
    double spike_height_ratio = 0.5;      // TODO: Decide
    double spike_min_price_action = 0.5;  // TODO: Decide
  } config;

  struct fetch_historical_quotes_args_t {
    int batch_size = 10000;
    int granularity_seconds = 0;
    double start_at = 0;
    std::string symbol;
  };

  Client(){};
  Client(std::map<std::string, std::string>);

  CurlClient place_order(order_t *order);

  std::string cancel_order(const int);
  std::string cancel_order(order_t *order);
  std::string fetch_account();
  std::string fetch_historical_quotes(const fetch_historical_quotes_args_t);
  std::string fetch_instruments(const std::vector<std::string>);
  std::string fetch_order(const int);
  std::string fetch_quote(char *);
  std::string fetch_quote(std::string);
  std::string fetch_trade(const int);

  quote_t parse_quote(const std::string &);

  void stream_account();

private:
  struct fetch_params_t {
    std::map<std::string, std::string> query_params;
    int timeout_seconds = 0;
    std::string url;
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::map<std::string, std::string> flags = {{"paper", "0"}};

  CurlClient fetch(const fetch_params_t);
  CurlClient post(const post_params_t);
  bool is_live();
  void load_config();
};
} // namespace Oanda

#endif
