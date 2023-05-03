#ifndef GLOBAL__types
#define GLOBAL__types

#include <map>    // std::map
#include <string> // std::string

namespace Global {
namespace t {
struct account_exit_prices_t {
  double current_profit = 0.00;
  double max_profit = 0.00;
  double stop_profit_loss = 0.00;
  double target_account_profit = 0.00;
  double target_max_profit = 0.00;
};

struct account_snapshot_t {
  double equity = 0.00;
  double margin_buying_power = 0.00;
  double margin_multiplier = 0.00;
  double max_equity = 0.00;
  double max_equity_timestamp = 0;
  double min_equity = 0.00;
  double min_equity_timestamp = 0;
  double original_equity = 0.00;
  double original_margin_buying_power = 0.00;
  double timestamp = 0;
  std::string api_key_id = "";
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

struct exit_prices_t {
  double max_loss = 0.00;
  double min_profit = 0.00;
  double trailing_stop_profit = 0.00;
};

struct order_win_result_streak_t {
  std::map<int, int> counts;
  int current = 0;
  int longest = 0;
};

struct performance_t {
  double current_balance = 0.00;
  double current_loss_streak_balance = 0.00;
  order_win_result_streak_t loss_streaks;
  double max_balance = 0.00;
  std::map<order_win_result_t, int> results;
  std::string symbol;
  order_win_result_streak_t win_streaks;
};

struct price_movement_average_t {
  double average = 0.00;
  long int count = 0;
};

struct price_movement_t {
  price_movement_average_t short_term_three_minute_one_second_variance;
  price_movement_average_t three_minute_one_second_variance;
};

struct one_sec_variance_avgs_t {
  double latest = 0.00;
  double running = 0.00;
};

struct quote_t {
  double ask = 0.00;
  double bid = 0.00;
  double price = 0.00;
  std::string symbol = "";
  double timestamp;
};
} // namespace t
} // namespace Global
#endif
