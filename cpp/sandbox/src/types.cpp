#ifndef GLOBAL__types
#define GLOBAL__types

#include <map> // std::map

namespace Global {
namespace t {
struct account_balance_t {
  double balance;
  double margin_buying_power;
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
  double upper_secure_profit = 0.00;
};

struct order_win_result_streak_t {
  std::map<int, int> counts;
  int current;
  int longest;
};

struct performance_t {
  double current_balance;
  order_win_result_streak_t loss_streaks;
  double max_balance;
  std::map<order_win_result_t, int> results;
  order_win_result_streak_t win_streaks;
};
} // namespace t
} // namespace Global
#endif
