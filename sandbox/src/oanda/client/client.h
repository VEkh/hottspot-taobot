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
    double margin_multiplier = 1.0;                      // TODO: Decide
    double margin_normalization_base_price_action = 0.0; // TODO: Decide
    double market_duration_hours = 120.0;
    std::string market_open_central_time = "07:00:00";
    double normalized_account_loss_ratio = 0.0;     // TODO: Decide
    bool only_stop_profit_in_consolidation = false; // TODO: Decide
    double quantity_decay_throttle = 0.0;           // TODO: Decide
    double range_min_height = 0.5;                  // TODO: Decide
    double reverse_percentile = 50.0;
    double secondary_reverse_percentile = 0.0;
    bool should_always_normalize = false;      // TODO: Decide
    bool should_always_reverse_profit = false; // TODO: Decide
    bool should_await_record_break = false;    // TODO: Decide
    bool should_enter_at_spike = true;         // TODO: Decide
    bool should_stop_profit = true;            // TODO: Decide
    bool should_trade_into_reversal = true;    // TODO: Decide
    double stop_loss_padding_ratio = 0.2;      // TODO: Delete after ML switch
    double stop_profit_target_price_action = 0.0;
    double stop_profit_version = 0.1;
    double warm_up_period_hours = 0.0; // TODO: Decide
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
