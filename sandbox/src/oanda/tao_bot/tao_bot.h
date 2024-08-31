#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "db/account_stat/account_stat.h"                // DB::AccountStat
#include "db/candle/candle.cpp"                          // DB::Candle
#include "db/margin_rate/margin_rate.h"                  // DB::MarginRate
#include "db/quote/quote.h"                              // DB::Quote
#include "deps.cpp"                                      // json
#include "lib/forex_availability/forex_availability.cpp" // ForexAvailability
#include "lib/formatted.cpp"                             // Formatted
#include "lib/pg/pg.cpp"                                 // Pg
#include "oanda/client/client.cpp"                       // Oanda::Client
#include "oanda/quote/quote.cpp"                         // Oanda::Quote
#include "oanda/types.cpp"                               // Oanda::t
#include "types.cpp"                                     // Global::t
#include <list>                                          // std::list
#include <map>                                           // std::map
#include <string>                                        // std::string
#include <time.h>                                        // time_t
#include <vector>                                        // std::map

namespace Oanda {
class TaoBot {
public:
  TaoBot(const std::string, std::map<std::string, std::string> &);

  void run();

private:
  using account_snapshot_t = Global::t::account_snapshot_t;
  using avg_one_sec_variances_t = Global::t::avg_one_sec_variances_t;
  using candle_bounds_t = DB::Candle::candle_bounds_t;
  using candle_t = Global::t::candle_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using margin_rate_t = DB::MarginRate::margin_rate_t;
  using order_action_t = Oanda::t::order_action_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;
  using order_time_in_force_t = Oanda::t::order_time_in_force_t;
  using order_type_t = Oanda::t::order_type_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Global::t::performance_t;
  using position_t = Oanda::t::position_t;
  using quote_t = Global::t::quote_t;
  using trade_status_t = Oanda::t::trade_status_t;

  static constexpr double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  static constexpr double MAX_ACCOUNT_LOSS_RATIO = -0.04;
  static constexpr double TARGET_ACCOUNT_PROFIT_RATIO = 0.04;
  static constexpr double TARGET_ACCOUNT_PROFIT_TRAILING_STOP = 0.001;

  std::map<const char *, const char *> ICONS = {
      {"BUY", "📈"},
      {"SELL", "📉"},
  };

  std::map<std::string, double> SPREAD_LIMITS = {
      {"AUD_CAD", 2.0e-4}, {"AUD_CHF", 2.8e-4}, {"AUD_JPY", 2.0e-2},
      {"AUD_NZD", 3.0e-4}, {"AUD_USD", 1.8e-4}, {"CAD_CHF", 2.6e-4},
      {"CAD_JPY", 2.2e-2}, {"CHF_JPY", 3.9e-2}, {"EUR_AUD", 3.0e-4},
      {"EUR_CAD", 2.4e-4}, {"EUR_CHF", 2.0e-4}, {"EUR_GBP", 2.0e-4},
      {"EUR_JPY", 2.0e-2}, {"EUR_NZD", 7.5e-4}, {"EUR_SEK", 5.0e-3},
      {"EUR_USD", 2.0e-4}, {"GBP_AUD", 4.2e-4}, {"GBP_CAD", 3.5e-4},
      {"GBP_CHF", 2.0e-4}, {"GBP_JPY", 3.0e-2}, {"GBP_NZD", 8.5e-4},
      {"GBP_PLN", 6.0e-3}, {"GBP_SGD", 6.0e-4}, {"GBP_USD", 2.4e-4},
      {"NZD_CAD", 2.4e-4}, {"NZD_JPY", 4.2e-2}, {"NZD_USD", 2.2e-4},
      {"USD_CAD", 2.4e-4}, {"USD_CHF", 2.0e-4}, {"USD_DKK", 1.6e-3},
      {"USD_JPY", 1.8e-2}, {"USD_SEK", 4.2e-3},
  };

  DB::AccountStat db_account_stat;
  DB::Candle db_candle;
  DB::MarginRate db_margin_rate;
  DB::Quote db_quote;
  ForexAvailability market_availability;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  Oanda::Quote quoter;
  Pg pg;
  account_snapshot_t account_snapshot;
  avg_one_sec_variances_t avg_one_sec_variances;
  exit_prices_t exit_prices;
  candle_t day_candle;
  double current_epoch = time(nullptr);
  double market_open_epoch;
  margin_rate_t margin_rate;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  quote_t current_quote;
  quote_t previous_quote;
  std::list<candle_t> latest_candles;
  std::list<quote_t> quotes;
  std::list<std::string> env_symbols;
  std::map<std::string, std::string> flags;
  std::string symbol;
  std::vector<position_t> closed_positions;
  time_t started_at = std::time(nullptr);

  bool has_super_profited();
  bool is_first_position_long();
  bool is_next_position_long();
  bool is_position_closed();
  bool max_account_loss_reached();
  bool should_close_position();
  bool should_open_position();
  bool should_read_candles();
  bool should_terminate();
  double account_profit_expanding_trailing_stop_ratio(const double);
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double convert_price(const double, const std::string, const std::string);
  double current_mid();
  double current_spread();
  double day_range_percentile(const double);
  double day_range_percentile(const order_t *, double);
  double margin_buying_power();
  double open_position_profit(const order_t *);
  double profit_percentage(const order_t *, const std::string);
  double spread_limit();
  exit_prices_t build_exit_prices();
  int compute_quantity();
  int order_duration(const order_t *, const std::string);
  int runtime();
  json fetch_account_snapshot();
  json fetch_order(const order_t *);
  json fetch_trade(const int);
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();

  std::pair<order_t, order_t> open_position(const order_action_t,
                                            const order_action_t, const char *,
                                            const int);

  std::string base_currency();
  void advance_current_epoch();
  void advance_current_epoch(const double);
  void await_market_open();
  void clear_stale_open_order();
  void close_position();
  void complete_filled_order(order_t *);
  void fetch_and_persist_margin_rates(const std::list<std::string>);
  void handle_partially_filled_close_order(const order_t *);
  void initialize(const std::string, std::map<std::string, std::string> &);
  void log_account_snapshot();
  void log_end_of_trading_period();
  void log_performance();
  void log_position();
  void log_position_results();
  void log_price_movement();
  void log_quote();
  void log_start_message();
  void log_timestamps();
  void open_and_persist_position();
  void read_candles();
  void read_quotes();
  void reset_orders();
  void reset_position();
  void set_close_order_prices();
  void set_execution_price(order_t *);
  void set_execution_price(order_t *, json);
  void set_market_open_epoch();
  void set_open_order_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *, order_t *);
  void update_account_snapshot();
  void update_margin_rate();
  void watch();
};
} // namespace Oanda

#endif
