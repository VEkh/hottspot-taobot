#ifndef ALPACA__TAO_BOT_H
#define ALPACA__TAO_BOT_H

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "alpaca/types.cpp"         // Alpaca::t
#include "lib/formatted.cpp"        // Formatted
#include "types.cpp"                // Global::t
#include <ctime>                    // std::time_t
#include <list>                     // std::list
#include <math.h>                   // INFINITY
#include <utility>                  // std::pair
#include <vector>                   // std::vector

namespace Alpaca {
class TaoBot {
public:
  using position_t = Alpaca::t::position_t;

  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using account_balance_t = Global::t::account_balance_t;
  using candlestick_t = Global::t::candlestick_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using hedge_info_t = Alpaca::t::hedge_info_t;
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_type_t = Alpaca::t::order_type_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Alpaca::t::performance_t;
  using price_movement_average_t = Global::t::price_movement_average_t;
  using price_movement_t = Global::t::price_movement_t;
  using quote_t = Alpaca::t::quote_t;
  using signal_t = Alpaca::t::signal_t;

  const double AVERAGE_TICK_PRICE_DELTA_PERIOD = 3.0 * 60.0;
  const double POSITION_TARGET_PROFIT_RATIO = 1.0e-6;
  const double MAX_ACCOUNT_LOSS_RATIO = 0.05;
  const double MAX_EXPECTED_LOSS_STREAK = 8;
  const int QUOTES_MAX_SIZE = 1e4;

  std::map<std::string, hedge_info_t> HEDGE_PAIRS = {
      {"AAPL", {.action = order_action_t::SELL, .symbol = "TQQQ"}},
      {"C", {.action = order_action_t::SELL, .symbol = "BAC"}},
      {"MSFT", {.action = order_action_t::SELL, .symbol = "TQQQ"}},
      {"SPY", {.action = order_action_t::SELL, .symbol = "QQQ"}},
      {"TSLA", {.action = order_action_t::SELL, .symbol = "QQQ"}},
  };

  std::map<const char *, const char *> ICONS = {
      {"buy", "📈"},
      {"sell", "📉"},
  };

  Alpaca::Client api_client;
  Alpaca::Client hedge_api_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  account_balance_t account_balance;
  account_balance_t hedge_account_balance;
  account_balance_t original_account_balance;
  account_balance_t original_hedge_account_balance;
  char *symbol;
  double quantity;
  exit_prices_t exit_prices;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  signal_t open_signal;
  signal_t stop_loss_signal;
  std::map<std::string, price_movement_t> price_movements;
  std::map<std::string, std::string> flags;
  std::map<std::string, std::vector<quote_t>> quotes;
  std::vector<position_t> closed_positions;

  account_balance_t fetch_account_balance(Alpaca::Client &);
  bool is_end_of_trading_period();
  bool is_holiday();
  bool is_market_open();
  bool is_position_closed();
  bool max_account_loss_reached();
  bool should_close_position(const order_t *, const order_t *);
  bool should_open_position(const order_t *);
  bool should_open_position(const signal_t &);
  bool should_stop_profit();
  bool should_terminate();
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double compute_quantity(const std::string &);
  double converted_signaler_price(const signal_t &);
  double current_price(const std::string &);
  double max_loss_ratio(const order_t *);
  double min_target_tick_movement();
  double loss_started_at = INFINITY;
  double open_position_profit(const order_t *, const order_t *);
  double position_target_movement();
  double price_movement_ratio(const std::string symbol_);
  double profit_percentage(const order_t *);
  double profit_started_at = INFINITY;
  double secured_profit_ratio(const order_t *);
  double volatility(const order_t *);
  exit_prices_t build_exit_prices(const order_t *);
  int order_duration(const order_t *);
  int profit_duration(const double);
  int runtime();
  int take_profit_after(const order_t *);
  int tradeable_symbols_count();
  json fetch_order(Alpaca::Client &, const order_t *);
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();
  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);
  quote_t read_streamed_quote(const std::string);
  price_movement_average_t
  price_movement_pair_ratio(std::vector<quote_t> &, std::vector<quote_t> &,
                            const price_movement_average_t);

  std::pair<double, double> compute_hedge_quantities();
  std::pair<order_t, order_t> open_position(Alpaca::Client,
                                            const order_action_t,
                                            const order_action_t, const char *,
                                            const double, std::string);
  std::string hedge_symbol();
  std::time_t started_at = std::time(nullptr);
  void await_market_open();
  void await_next_poll();
  void cancel_stale_open_order(Alpaca::Client &, const order_t *);
  void cancel_stale_open_orders();
  void close_position(Alpaca::Client &, order_t *, order_t *, const double,
                      const bool);
  void close_positions();
  void fetch_quotes();
  void initialize(char *, std::map<std::string, std::string> &);
  void load_performance();
  void load_price_movement(const std::string &);
  void load_quotes(const std::string &);
  void log_account_balance(account_balance_t, account_balance_t, const char *);
  void log_account_balances();
  void log_end_of_trading_period();
  void log_performance();
  void log_position(const order_t *, const order_t *, const char *);
  void log_positions();
  void log_positions_profit();
  void log_position_results();
  void log_price_movement(const std::string &);
  void log_price_movements();
  void log_quote(const std::string &);
  void log_quotes();
  void log_signal(const signal_t &, const char *);
  void log_signals();
  void log_start_message();
  void log_timestamps();
  void open_pair_signaled_position();
  void open_positions();
  void reset_position();
  void set_close_order_prices(Alpaca::Client &, order_t *, order_t *);
  void set_close_position_prices();
  void set_execution_price(Alpaca::Client &, order_t *);
  void set_loss_started_at();
  void set_open_order_prices(Alpaca::Client &, order_t *);
  void set_open_position_prices();
  void set_open_signal();
  void set_position_status();
  void set_price_movement(const std::string &);
  void set_price_movements();
  void set_profit(order_t *, const order_t *);
  void set_profit(order_t *, const std::vector<quote_t> *);
  void set_profit_started_at();
  void set_stop_loss_signal();
  void set_status(Alpaca::Client &, order_t *order);
  void watch();
  void write_performance();
  void write_price_movement(const std::string &, const price_movement_t &);
  void write_quotes(const std::string &);
};
} // namespace Alpaca

#endif
