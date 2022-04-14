#ifndef GLOBAL__types
#define GLOBAL__types

#include <map> // std::map

namespace Global {
namespace t {
struct account_balance_t {
  double balance;
  double margin_buying_power;
  double margin_multiplier;
};

struct candlestick_t {
  std::string clock_time;
  double close;
  double high;
  double low;
  double open;
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

struct exit_prices_t {
  double lower_secure_profit = 0.00;
  double max_loss = 0.00;
  double min_profit = 0.00;
  double position_target_movement = 0.00;
  double upper_secure_profit = 0.00;
};

struct order_win_result_streak_t {
  std::map<int, int> counts;
  int current = 0;
  int longest = 0;
};

struct performance_t {
  bool are_funds_sufficient = true;
  int closed_positions_count = 0;
  double current_balance = 0.00;
  double current_loss_streak_balance = 0.00;
  bool is_position_open = false;
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
  price_movement_average_t ratio_from_hedge;
  price_movement_average_t short_term_three_minute_one_second_variance;
  price_movement_average_t three_minute_one_second_variance;
};
} // namespace t
} // namespace Global
#endif
