#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "db/account_stat/account_stat.h"          // DB::AccountStat
#include "db/candle/candle.cpp"                    // DB::Candle
#include "db/margin_rate/margin_rate.h"            // DB::MarginRate
#include "db/position/position.cpp"                // DB::Position
#include "db/quote/quote.h"                        // DB::Quote
#include "db/utils/utils.cpp"                      // DB::Utils
#include "deps.cpp"                                // json
#include "lib/backtest/backtest.cpp"               // Backtest
#include "lib/formatted.cpp"                       // Formatted
#include "lib/market_availability/forex/forex.cpp" // MarketAvailability::Forex
#include "lib/pg/pg.cpp"                           // Pg
#include "oanda/client/client.cpp"                 // Oanda::Client
#include "oanda/mock/client/client.cpp"            // Oanda::Mock::Client
#include "oanda/quote/quote.cpp"                   // Oanda::Quote
#include "oanda/types.cpp"                         // Oanda::t
#include "types.cpp"                               // Global::t
#include <list>                                    // std::list
#include <map>                                     // std::map
#include <string>                                  // std::string
#include <time.h>                                  // time_t
#include <vector>                                  // std::map

namespace Oanda {
class TaoBot {
public:
  TaoBot(const std::string, std::map<std::string, std::string> &);

  void run();

private:
  using account_snapshot_t = Global::t::account_snapshot_t;
  using candle_bounds_t = DB::Candle::candle_bounds_t;
  using candle_t = Global::t::candle_t;
  using currency_t = Oanda::t::currency_t;
  using db_position_t = DB::Position::position_t;
  using execution_strategy_t = Global::t::execution_strategy_t; // TODO: Decide
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
  using reversal_t = Global::t::reversal_t;
  using reversal_type_t = Global::t::reversal_type_t;
  using reversals_t = Global::t::reversals_t;
  using spike_candles_t = Global::t::spike_candles_t;
  using stop_profit_type_t = Global::t::stop_profit_type_t;
  using trade_status_t = Oanda::t::trade_status_t;
  using trend_meta_t = Global::t::trend_meta_t;
  using trend_t = Global::t::trend_t;

  // TODO: Decide
  struct build_exit_prices_args_t {
    order_action_t action;
    candle_t day_candle;
    reversal_t entry_reversal;
    double execution_price;
  };

  struct convert_price_args_t {
    bool debug = false;
    std::string from;
    double price;
    std::string to;
  };

  static constexpr const char *ACCOUNT_CURRENCY = "USD";
  static constexpr double EQUATOR_PERCENTILE = 50.0;
  static constexpr double SPIKE_ENTRY_SCORE = 5.0;
  static constexpr double SPIKE_HEIGHT_RATIO = 0.5;
  static constexpr double STOP_LOSS_PADDING_RATIO = 0.2;
  static constexpr double TREND_SLIP_PERCENTILE = 80.0;
  static constexpr int MAX_LOSS_STREAK = 2;
  static constexpr int REVERSAL_TIMEFRAME_MINUTES = 120;
  static constexpr int SPIKE_DURATION_MINUTES = 60;

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

  Backtest backtest;
  DB::AccountStat db_account_stat;
  DB::Candle db_candle;
  DB::MarginRate db_margin_rate;
  DB::Position db_position;
  DB::Quote db_quote;
  DB::Utils db_utils;
  MarketAvailability::Forex market_availability;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  Oanda::Mock::Client mock_api_client;
  Oanda::Quote quoter;
  Pg pg;
  account_snapshot_t account_snapshot;
  bool has_stopped_profit = false; // TODO: Decide
  exit_prices_t exit_prices;
  candle_t day_candle;
  candle_t warm_up_candle; // TODO: Decide
  currency_t currency;
  double current_epoch = time(nullptr);
  margin_rate_t margin_rate;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  quote_t current_quote;
  quote_t previous_quote;
  reversal_t entry_reversal;
  reversals_t reversals;
  spike_candles_t spike_candles;
  std::list<candle_t> latest_candles;
  std::list<quote_t> quotes;
  std::list<std::string> env_symbols;
  std::map<std::string, std::string> flags;
  std::string symbol;
  std::vector<position_t> closed_positions;
  time_t started_at = std::time(nullptr);
  trend_meta_t current_trend;

  bool can_open_position();
  bool did_last_position_stop_profit(); // TODO: Decide
  bool has_just_reached_stop_profit();
  bool is_end_of_quotes();
  bool is_entry_signal_present();
  bool is_next_position_long();
  bool is_record_break_entry_signal_present(); // TODO: Decide
  bool is_position_closed();
  bool is_range_min_height(); // TODO: Decide
  bool is_reversal_after(const reversal_t, const double);
  bool is_spiking();
  bool is_trend_slipping(const order_t *);
  bool is_trend_slipping(const order_t *, const double); // TODO: Decide
  bool is_trending();                                    // TODO: Decide
  bool is_trending(const trend_meta_t);                  // TODO: Decide
  bool max_account_loss_reached();
  bool should_close_position();
  bool should_nullify_entry_reversal(); // TODO: Decide
  bool should_open_position();
  bool should_read_candles();
  bool should_reverse_loss();
  bool should_reverse_profit(); // TODO: Decide
  bool should_stop_profit();
  bool should_terminate();
  bool should_toggle_is_trending(order_t &, order_t &); // TODO: Decide
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double convert_price(const convert_price_args_t);
  double current_mid();
  double day_range_percentile(candle_t, const double, const bool);
  double day_range_percentile(candle_t, const order_t *, double);
  double margin_buying_power();
  double margin_normalization_factor();  // TODO: Decide
  double normalized_margin_multiplier(); // TODO: Decide
  double open_position_profit(const order_t *);
  double profit_percentage(const order_t *, const std::string);
  double reverse_percentile(); // TODO: Decide
  double spike_score(spike_candles_t);
  double spread_limit();
  double stop_profit_version(); // TODO: Decide

  execution_strategy_t execution_strategy(); // TODO: Decide

  exit_prices_t build_exit_prices(build_exit_prices_args_t); // TODO: Decide
  int order_duration(const order_t *, const std::string);
  int runtime();
  json fetch_order(const order_t *);
  json fetch_trade(const order_t *);
  long int compute_quantity();
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();
  quote_t get_real_time_quote(const std::string);

  reversal_t latest_record_as_reversal(const reversal_type_t);
  reversal_t latest_record_reversal(reversals_t &,
                                    const reversal_type_t); // TODO: Decide
  reversal_t
  latest_record_reversal_after(reversals_t &, const double,
                               const reversal_type_t); // TODO: Decide

  reversal_t latest_reversal(reversals_t &, const reversal_type_t,
                             const bool); // TODO: Decide

  reversal_t latest_reversal_after(reversals_t &, const double,
                                   const reversal_type_t);

  reversal_t nearer_reversal(const reversal_t, const reversal_t, const double);

  std::pair<order_t, order_t> open_position(const order_action_t,
                                            const order_action_t, const char *,
                                            const long int);

  std::string stop_profit_type_name(const order_t *);

  stop_profit_type_t stop_profit_type(candle_t, const double);
  stop_profit_type_t stop_profit_type(const order_t *);

  void advance_current_epoch();
  void advance_current_epoch(const double);
  void build_currency();
  void build_day_candle();
  void build_spike_candles();
  void build_reversals(reversals_t &, const bool);
  void clear_stale_open_order();
  void close_position();
  void complete_filled_order(order_t *);
  void ensure_market_is_open();
  void ensure_spread_limit();
  void ensure_symbol(const std::string);
  void fetch_and_persist_margin_rates(const std::list<std::string>);
  void force_init_reversal_await(); // TODO: Decide
  void handle_partially_filled_close_order(const order_t *);
  void initialize(const std::string, std::map<std::string, std::string> &);
  void initialize_current_trend(); // TODO: Decide
  void log_account_snapshot();
  void log_end_of_trading_period();
  void log_env_symbols();
  void log_performance();
  void log_position();
  void log_position_results();
  void log_price_action();
  void log_quote();
  void log_reversal_metadata();
  void log_reversals(reversals_t &);
  void log_spike_candles();
  void log_start_message();
  void log_timestamps();
  void open_and_persist_position();
  void read_candles();
  void read_closed_positions();
  void read_quotes();
  void reset_backtest();
  void reset_orders();
  void reset_position();
  void set_close_order_prices();
  void set_current_trend();
  void set_execution_price(order_t *);
  void set_execution_price(order_t *, json);
  void set_open_order_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, order_t *);
  void set_status(order_t *, order_t *);
  void set_to_account_currency_ratio(order_t *);
  void toggle_is_trending(const order_t &); // TODO: Decide
  void update_account_snapshot(const bool);
  void update_margin_rate();
  void watch();
  void write_close_position();
  void write_open_position();
};
} // namespace Oanda

#endif
