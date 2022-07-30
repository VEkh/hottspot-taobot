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
  using account_exit_prices_t = Alpaca::t::account_exit_prices_t;
  using candlestick_t = Global::t::candlestick_t;
  using exit_prices_t = Global::t::exit_prices_t;
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

  const double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  const double POSITION_TARGET_PROFIT_RATIO = 1.0e-6;
  const double MAX_ACCOUNT_LOSS_RATIO = 0.02;
  const double TARGET_DAILY_PROFIT = 0.0105;
  const double TARGET_DAILY_PROFIT_TRAILING_STOP = 0.001;
  const int PRICE_MOVEMENT_SAMPLE_SIZE = 5e5;
  const int QUOTES_MAX_SIZE = 4e2;

  std::map<const char *, const char *> ICONS = {
      {"buy", "📈"},
      {"sell", "📉"},
  };

  Alpaca::Client api_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  account_balance_t account_balance;
  account_balance_t original_account_balance;
  char *symbol;
  double quantity;
  exit_prices_t exit_prices;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  std::map<std::string, price_movement_t> price_movements;
  std::map<std::string, std::string> flags;
  std::map<std::string, std::vector<quote_t>> quotes;
  std::vector<position_t> closed_positions;

  account_balance_t get_account_balance(Alpaca::Client &);
  account_balance_t get_account_balance(Alpaca::Client &,
                                        const account_balance_t &);

  account_exit_prices_t build_account_exit_prices();

  bool is_end_of_trading_period();
  bool is_holiday();
  bool is_market_open();
  bool is_position_closed();
  bool max_account_loss_reached();
  bool should_close_position(const order_t *, const order_t *);
  bool should_open_position(const order_t *);
  bool should_open_position();
  bool should_stop_profit();
  bool should_terminate();
  double closed_position_profit(const position_t &);
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double compute_quantity(const std::string &);
  double current_price(const std::string &);
  double min_target_tick_movement();
  double open_position_profit(const order_t *);
  double position_target_movement();
  double price_movement_ratio(const std::string symbol_);
  double profit_percentage(const order_t *);
  double secured_profit_ratio(const order_t *);
  double target_daily_profit(const double);
  double target_daily_profit_trailing_stop();
  double volatility(const order_t *);
  double volatility(const std::string &);
  exit_prices_t build_exit_prices(const order_t *);
  int order_duration(const order_t *);
  int profit_duration(const double);
  int runtime();
  int tradeable_symbols_count();
  json fetch_account_balance(Alpaca::Client &);
  json fetch_order(Alpaca::Client &, const order_t *);
  json read_streamed_account();
  order_action_t opposite_direction(const order_action_t);
  order_win_result_t order_win_result(const position_t);
  performance_t build_performance();
  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);
  quote_t read_streamed_quote(const std::string);

  std::pair<order_t, order_t> open_position(Alpaca::Client,
                                            const order_action_t,
                                            const order_action_t, const char *,
                                            const double, std::string);
  std::time_t started_at = std::time(nullptr);
  void await_market_open();
  void await_next_poll();
  void cancel_stale_open_order();
  void close_position(const double, const bool);
  void fetch_and_persist_quote();
  void initialize(char *, std::map<std::string, std::string> &);
  void load_performance();
  void load_price_movement(const std::string &);
  void load_quotes(const std::string &);
  void log_account_balance();
  void log_end_of_trading_period();
  void log_performance();
  void log_position();
  void log_positions();
  void log_position_results();
  void log_price_movement();
  void log_quote();
  void log_start_message();
  void log_timestamps();
  void open_and_persist_position();
  void reset_position();
  void set_close_order_prices();
  void set_execution_price(Alpaca::Client &, order_t *);
  void set_open_order_prices();
  void set_position_status();
  void set_price_movement();
  void set_and_persist_price_movement();
  void set_profit(order_t *, const order_t *);
  void set_profit(order_t *, const std::vector<quote_t> *);
  void set_status(Alpaca::Client &, order_t *order);
  void update_account_balance();
  void watch();
  void write_performance();
  void write_price_movement();
  void write_quotes();
};
} // namespace Alpaca

#endif
