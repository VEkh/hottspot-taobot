#ifndef ETRADE__STOCK_BOT_H
#define ETRADE__STOCK_BOT_H

#include "etrade/client/client.cpp" // ETrade::Client
#include "etrade/deps.cpp"          // json
#include "etrade/types.cpp"         // ETrade::t
#include "lib/formatted.cpp"        // Formatted
#include <map>                      // std::map
#include <string>                   // std::string
#include <vector>                   // std::vector

namespace ETrade {
class StockBot {
public:
  StockBot(char *, int, std::map<std::string, std::string> &);

  void run();

private:
  using account_balance_t = ETrade::t::account_balance_t;
  using closed_positions_stats_t = ETrade::t::closed_positions_stats_t;
  using exit_prices_t = ETrade::t::exit_prices_t;
  using order_action_t = ETrade::t::order_action_t;
  using order_status_t = ETrade::t::order_status_t;
  using order_t = ETrade::t::order_t;
  using order_type_t = ETrade::t::order_type_t;
  using order_win_result_t = ETrade::t::order_win_result_t;
  using order_win_result_streak_t = ETrade::t::order_win_result_streak_t;
  using position_t = ETrade::t::position_t;
  using quote_t = ETrade::t::quote_t;

  const double AVERAGE_TICK_PRICE_DELTA_PERIOD = 5.0 * 60.0;
  const double BUY_SELL_RATIO_DOOR_THRESHOLD = 1.35;
  const double POLLING_INTERVAL_SECONDS = 1.0;
  const double SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS = 2 * 60;

  const int MAX_EXPECTED_LOSS_STREAK = 8;

  bool FLAG_MARTINGALE = false;
  bool FLAG_NORMALIZE_QUANTITY = false;

  std::map<const char *, const char *> ICONS = {
      {"BUY", "📈"},
      {"SELL_SHORT", "📉"},
  };

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  account_balance_t account_balance;
  account_balance_t original_account_balance;
  bool is_long_position;
  char *symbol;
  double average_tick_price_delta = 0.00;
  double long_average_buy_sell_ratio;
  double long_average_sell_buy_ratio;
  double short_average_buy_sell_ratio;
  double short_average_sell_buy_ratio;
  exit_prices_t exit_prices;
  int insufficient_funds_at_loss = 0;
  int quantity_mulitiplier;
  int quantity;
  json placed_orders;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;

  std::vector<position_t> closed_positions;
  std::vector<quote_t> quotes;

  account_balance_t fetch_account_balance();

  bool should_close_position();
  bool should_open_position();
  bool should_terminate();

  double compute_min_profit_price_range_ratio(const double);
  double profit_percentage(const order_t *);

  int compute_normalized_quantity();
  int martingale_quantity_multiplier();

  closed_positions_stats_t build_closed_positions_stats();
  exit_prices_t build_exit_prices();
  json fetch_order(const order_t *);
  order_win_result_t order_win_result(const order_t *);

  std::map<int, std::map<const char *, double>>
  compute_moving_buy_sell_ratio_average(std::vector<int> &);

  void await_market_open();
  void cancel_stale_open_order();
  void close_position();
  void fetch_quote();
  void initialize(char *, int, std::map<std::string, std::string> &flags);
  void log_account_balance();
  void log_average_tick_price_delta();
  void log_closed_positions();
  void log_end_of_day();
  void log_position();
  void log_position_results();
  void log_quote();
  void log_start_message();
  void open_position();
  void reset_position();
  void set_and_log_buy_sell_ratios();
  void set_average_tick_price_delta();
  void set_execution_price(order_t *);
  void set_movement_moving_averages();
  void set_open_position_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *);
  void watch();
};
} // namespace ETrade

#endif
