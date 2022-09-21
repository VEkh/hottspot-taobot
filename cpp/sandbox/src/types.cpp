#ifndef GLOBAL__types
#define GLOBAL__types

#include <map>    // std::map
#include <string> // std::string

namespace Global {
namespace t {
struct account_balance_t {
  double balance = 0.0;
  double margin_buying_power;
  double margin_multiplier;
  double max_balance = 0.00;
  long int max_balance_timestamp = 0;
  double min_balance = 0.00;
  long int min_balance_timestamp = 0;
  double original_balance = 0.00;
  double original_margin_buying_power = 0.00;
  long int timestamp = 0;
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

struct account_exit_prices_t {
  double current_profit = 0.00;
  double max_profit = 0.00;
  double stop_loss_profit = 0.00;
  double target_account_profit = 0.00;
  double target_max_profit = 0.00;
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
  price_movement_average_t ratio_from_pair;
  price_movement_average_t ratio_to_pair;
  price_movement_average_t short_term_three_minute_one_second_variance;
  price_movement_average_t three_minute_one_second_variance;
};
} // namespace t
} // namespace Global
#endif
