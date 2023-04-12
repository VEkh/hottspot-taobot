#ifndef ALPACA__TAO_BOT_H
#define ALPACA__TAO_BOT_H

#include "alpaca/client/client.cpp"             // Alpaca::Client
#include "alpaca/quote/quote.cpp"               // Alpaca::Quote
#include "alpaca/types.cpp"                     // Alpaca::t
#include "backtest/backtest.cpp"                // Alpaca::TaoBotBacktest
#include "lib/formatted.cpp"                    // Formatted
#include "lib/pg/pg.cpp"                        // Pg
#include "models/account_stat/account_stat.cpp" // DB::AccountStat
#include "models/position/position.cpp"         // DB::Position
#include "types.cpp"                            // Global::t
#include <list>                                 // std::list
#include <math.h>                               // INFINITY
#include <time.h>                               // time
#include <utility>                              // std::pair
#include <vector>                               // std::vector

namespace Alpaca {
class TaoBot {
public:
  using position_t = Alpaca::t::position_t;

  TaoBot(std::string, std::map<std::string, std::string> &);

  void run();

private:
  using account_snapshot_t = Global::t::account_snapshot_t;
  using account_exit_prices_t = Global::t::account_exit_prices_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using one_sec_variance_avgs_t = Global::t::one_sec_variance_avgs_t;
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_type_t = Alpaca::t::order_type_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Alpaca::t::performance_t;
  using price_movement_average_t =
      Global::t::price_movement_average_t;              // NOTE: Deprecated
  using price_movement_t = Global::t::price_movement_t; // NOTE: Deprecated
  using quote_scoreboard_t = Alpaca::t::quote_scoreboard_t;
  using quote_t = Global::t::quote_t;

  constexpr static double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  constexpr static double MAX_ACCOUNT_LOSS_RATIO = -0.03;
  constexpr static double POSITION_TARGET_PROFIT_RATIO = 1.0e-6;
  constexpr static double TARGET_ACCOUNT_PROFIT_RATIO = 0.03;
  constexpr static double TARGET_ACCOUNT_PROFIT_TRAILING_STOP = 0.001;
  const static int CONSOLIDATION_TIME_SECONDS = 45 * 60;
  const static int PRICE_MOVEMENT_SAMPLE_SIZE = 5e5;
  const static int QUOTES_MAX_SIZE = 8e3;

  std::map<const char *, const char *> ICONS = {
      {"buy", "📈"},
      {"sell", "📉"},
  };

  Alpaca::Client api_client;
  Alpaca::Quote quoter;
  Alpaca::TaoBotBacktest backtest;
  DB::AccountStat db_account_stat;
  DB::Position db_position;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  Pg pg;
  account_snapshot_t account_snapshot;
  double current_epoch = time(nullptr);
  double quantity;
  double started_at = time(nullptr);
  int init_closed_positions_count = 0;
  exit_prices_t exit_prices;
  one_sec_variance_avgs_t one_sec_variance_avgs;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  price_movement_t price_movement; // NOTE: Deprecated
  std::map<std::string, std::string> flags;
  std::string symbol;
  std::vector<position_t> closed_positions;
  std::vector<quote_t> quotes;

  account_snapshot_t get_account_balance(); // NOTE: Deprecated
  account_snapshot_t
  get_account_balance(const account_snapshot_t &); // NOTE: Deprecated

  account_exit_prices_t build_account_exit_prices();

  bool has_super_profited();
  bool is_breaking_out();
  bool is_early_close_day();
  bool is_end_of_trading_period();
  bool is_first_position_long();
  bool is_holiday();
  bool is_market_day();
  bool is_market_open();
  bool is_next_position_long();
  bool is_position_closed();
  bool is_price_moving();
  bool max_account_loss_reached();
  bool new_positions_opened();
  bool should_close_position();
  bool should_open_position();
  bool should_stop_profit();
  bool should_terminate();
  double account_profit_expanding_trailing_stop_ratio(const double);
  double batch_volatility(); // NOTE: Deprecated
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double compute_quantity();
  double current_price();
  double dynamic_one_sec_variance();
  double min_target_tick_movement();
  double open_position_profit(const order_t *);
  double profit_percentage(const order_t *);
  double target_account_profit();
  double target_position_profit();
  double volatility();
  exit_prices_t build_exit_prices();
  int order_duration(const order_t *);
  int profit_duration(const double);
  int runtime();
  int tradeable_symbols_count();
  json fetch_account_balance(); // NOTE: Deprecated
  json fetch_order(const order_t *);
  json read_streamed_account();
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();

  std::pair<double, double> get_quote_price_range();
  std::pair<order_t, order_t> open_position(const order_action_t,
                                            const order_action_t, const char *,
                                            const double);
  void advance_current_epoch();
  void advance_current_epoch(const double);
  void await_market_open();
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
  void open_and_persist_position();
  void read_price_movement();
  void read_quotes();
  void reset_position();
  void set_close_order_prices();
  void set_execution_price(order_t *);
  void set_open_order_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *order);
  void update_account_snapshot();
  void watch();
  void write_account_performance();
  void write_close_position();
  void write_open_position();
};
} // namespace Alpaca

#endif
