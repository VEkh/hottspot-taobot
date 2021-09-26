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

struct order_win_result_streak_t {
  std::map<int, int> counts;
  int current;
  int longest;
};

struct closed_positions_stats_t {
  order_win_result_streak_t loss_streaks;
  std::map<order_win_result_t, int> results;
  double total_profit;
  order_win_result_streak_t win_streaks;
};

struct exit_prices_t {
  double max_loss = 0.00;
  double min_profit = 0.00;
  double secure_profit_lower = 0.00;
  double secure_profit_upper = 0.00;
};

struct quote_t {
  double price;
  long int timestamp;
};
} // namespace t
} // namespace Global
#endif
