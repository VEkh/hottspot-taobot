#ifndef ALPACA__TAO_BOT_H
#define ALPACA__TAO_BOT_H

#include "alpaca/client/client.cpp"         // Alpaca::Client
#include "alpaca/quote/quote.cpp"           // Alpaca::Quote
#include "alpaca/types.cpp"                 // Alpaca::t
#include "backtest/backtest.cpp"            // Alpaca::TaoBotBacktest
#include "db/account_stat/account_stat.cpp" // DB::AccountStat
#include "db/candle/candle.cpp"             // DB::Candle
#include "db/position/position.cpp"         // DB::Position
#include "db/utils/utils.cpp"               // DB::Utils
#include "deps.cpp"                         // json
#include "lib/formatted.cpp"                // Formatted
#include "lib/pg/pg.cpp"                    // Pg
#include "types.cpp"                        // Global::t
#include <list>                             // std::list
#include <time.h>                           // time
#include <utility>                          // std::pair
#include <vector>                           // std::vector

namespace Alpaca {
class TaoBot {
public:
  using position_t = Alpaca::t::position_t;

  TaoBot(const std::string, std::map<std::string, std::string> &);

  void run();

private:
  using account_exit_prices_t = Global::t::account_exit_prices_t;
  using account_snapshot_t = Global::t::account_snapshot_t;
  using avg_one_sec_variances_t = Global::t::avg_one_sec_variances_t;
  using candle_t = DB::Candle::candle_t;
  using db_position_t = DB::Position::position_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_time_in_force_t = Alpaca::t::order_time_in_force_t;
  using order_type_t = Alpaca::t::order_type_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Global::t::performance_t;
  using quote_t = Global::t::quote_t;
  using reversal_t = Alpaca::t::reversal_t;
  using reversal_type_t = Alpaca::t::reversal_type_t;
  using reversals_t = Alpaca::t::reversals_t;
  using trend_meta_t = Global::t::trend_meta_t;
  using trend_t = Global::t::trend_t;

  constexpr static double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  constexpr static double TARGET_ACCOUNT_PROFIT_TRAILING_STOP = 0.001;

  std::map<const char *, const char *> ICONS = {
      {"buy", "📈"},
      {"sell", "📉"},
  };

  Alpaca::Client api_client;
  Alpaca::Quote quoter;
  Alpaca::TaoBotBacktest backtest;
  DB::AccountStat db_account_stat;
  DB::Candle db_candle;
  DB::Position db_position;
  DB::Utils db_utils;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg pg;
  account_snapshot_t account_snapshot;
  avg_one_sec_variances_t avg_one_sec_variances;
  double current_epoch = time(nullptr);
  double market_open_epoch;
  double quantity;
  double started_at = time(nullptr);
  int tradeable_symbols_count = 1;
  exit_prices_t exit_prices;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  reversal_t entry_reversal;
  reversals_t reversals;
  reversals_t secondary_reversals;
  std::list<candle_t> latest_candles;
  std::list<quote_t> quotes;
  std::map<std::string, std::string> flags;
  std::string symbol;
  std::vector<position_t> closed_positions;
  trend_meta_t current_trend;

  account_exit_prices_t build_account_exit_prices();

  bool does_position_exist();
  bool has_reversal_been_used(const reversal_t);
  bool has_super_profited();
  bool is_early_close_day();
  bool is_end_of_trading_period();
  bool is_entry_signal_present();
  bool is_first_position_long();
  bool is_market_open();
  bool is_next_position_long();
  bool is_position_closed();
  bool is_quote_stale(const quote_t, const double);
  bool is_trending();
  bool is_within_entry_window(const reversal_t);
  bool max_account_loss_reached();
  bool should_close_position();
  bool should_open_position();
  bool should_stop_profit();
  bool should_terminate();
  bool should_toggle_is_trending(const order_t &);
  bool should_use_price_movement();
  double account_profit_expanding_trailing_stop_ratio(const double);
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double compute_quantity();
  double current_mid();
  double open_position_profit(const order_t *);
  double profit_percentage(const order_t *, std::string);
  double target_account_profit_ratio();
  exit_prices_t build_exit_prices();
  int order_duration(const order_t *, const std::string);
  int profit_duration(const double);
  int runtime();
  json fetch_order(const order_t *);
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();
  reversal_t latest_record_reversal(reversals_t &, const std::string);
  reversal_t latest_reversal(reversals_t &, const std::string);
  std::pair<order_t, order_t> open_position(const order_action_t,
                                            const order_action_t, const char *,
                                            const double);

  void advance_current_epoch();
  void advance_current_epoch(const double);
  void await_market_open();
  void build_reversals(reversals_t &);
  void cancel_stale_open_order();
  void close_position();
  void fetch_and_persist_quote(const bool);
  void initialize(std::string, std::map<std::string, std::string> &);
  void log_account_snapshot();
  void log_end_of_trading_period();
  void log_performance();
  void log_position();
  void log_position_results();
  void log_positions();
  void log_price_movement();
  void log_quote();
  void log_start_message();
  void log_timestamps();
  void log_reversal_metadata();
  void log_reversals(reversals_t &);
  void open_and_persist_position();
  void read_candles();
  void read_closed_positions();
  void read_price_movement();
  void read_quotes();
  void reset_backtest();
  void reset_position();
  void set_close_order_prices();
  void set_execution_price(order_t *);
  void set_market_open_epoch();
  void set_open_order_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *);
  void toggle_is_trending(const order_t &);
  void update_account_snapshot(const bool);
  void watch();
  void write_close_position();
  void write_open_position();
};
} // namespace Alpaca

#endif
