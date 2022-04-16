#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "deps.cpp"                // json
#include "lib/formatted.cpp"       // Formatted
#include "oanda/client/client.cpp" // Oanda::Client
#include "oanda/types.cpp"         // Oanda::t
#include "types.cpp"               // Global::t
#include <list>                    // std::list
#include <map>                     // std::map
#include <string>                  // std::string
#include <vector>                  // std::map

namespace Oanda {
class TaoBot {
public:
  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using account_balance_t = Global::t::account_balance_t;
  using candlestick_t = Global::t::candlestick_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using order_action_t = Oanda::t::order_action_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;
  using order_time_in_force_t = Oanda::t::order_time_in_force_t;
  using order_type_t = Oanda::t::order_type_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using performance_t = Global::t::performance_t;
  using position_t = Oanda::t::position_t;
  using price_movement_t = Global::t::price_movement_t;
  using quote_t = Oanda::t::quote_t;
  using trade_status_t = Oanda::t::trade_status_t;

  const double AVERAGE_TICK_PRICE_DELTA_PERIOD = 3.0 * 60.0;
  const double MAX_ACCOUNT_LOSS_RATIO = 0.05;
  const double MAX_SPREAD_TO_OPEN_RATIO = 3.0;
  const double MIN_TARGET_TICK_MOVEMENT = 40.0;
  const double POLLING_INTERVAL_SECONDS = 1.0;
  const int MAX_EXPECTED_LOSS_STREAK = 18;

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

  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  account_balance_t account_balance;
  account_balance_t original_account_balance;
  bool is_long_position = true;
  char *symbol;
  exit_prices_t exit_prices;
  int quantity;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  performance_t performance;
  price_movement_t price_movement;
  std::list<candlestick_t> candlesticks;
  std::map<std::string, std::string> flags;
  std::vector<position_t> closed_positions;
  std::vector<quote_t> quotes;

  account_balance_t fetch_account_balance();
  bool awaited_loss_leader();
  bool is_end_of_trading_period();
  bool is_market_open();
  bool max_account_loss_reached();
  bool should_close_position();
  bool should_open_position();
  bool should_terminate();
  double base_quantity();
  double compute_profit(const order_t *, const order_t *);
  double compute_profit(const order_t *, const quote_t *);
  double convert_price(const double, const std::string, const std::string);
  double current_spread();
  double loss_to_recover();
  double max_affordable_quantity();
  double position_target_movement();
  double profit_percentage(const order_t *);
  double secured_profit_ratio();
  double spread_limit();
  exit_prices_t build_exit_prices();
  performance_t build_performance();
  performance_t get_loss_leader(std::list<performance_t> &);
  int compute_quantity();
  int runtime();
  json fetch_order(const order_t *);
  json fetch_trade(const int);
  order_win_result_t order_win_result(const order_t *);
  std::list<performance_t> read_sibling_performances();
  std::string base_currency();
  void await_market_open();
  void build_candlesticks();
  void clear_stale_open_order();
  void complete_filled_order(order_t *);
  void close_position();
  void fetch_quote();
  void handle_partially_filled_close_order(const order_t *);
  void initialize(char *, std::map<std::string, std::string> &);
  void load_performance();
  void load_price_movement();
  void log_account_balance();
  void log_candlesticks();
  void log_end_of_trading_period();
  void log_performance();
  void log_position();
  void log_position_results();
  void log_price_movement();
  void log_quote();
  void log_start_message();
  void log_timestamps();
  void open_position();
  void reset_position();
  void set_close_position_prices();
  void set_execution_price(order_t *);
  void set_execution_price(order_t *, json);
  void set_open_position_prices();
  void set_position_status();
  void set_price_movement();
  void set_profit(order_t *, const order_t *);
  void set_profit(order_t *);
  void set_status(order_t *, order_t *);
  void set_trade_direction();
  void watch();
  void write_performance();
  void write_price_movement();
};
} // namespace Oanda

#endif
