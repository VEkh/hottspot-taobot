#ifndef ETRADE__types
#define ETRADE__types

#include <map>     // std::map
#include <utility> // std::pair

namespace ETrade {
namespace t {
enum order_action_t {
  BUY,
  BUY_TO_COVER,
  SELL,
  SELL_SHORT,
};

enum order_status_t {
  ORDER_CANCELLED,
  ORDER_CANCEL_REQUESTED,
  ORDER_EXECUTED,
  ORDER_OPEN,
  ORDER_PARTIAL,
  ORDER_PENDING,
};

enum order_type_t {
  LIMIT,
  MARKET,
  STOP_LIMIT,
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

struct account_balance_t {
  double balance;
  double day_trading_margin_buying_power;
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

struct order_t {
  order_action_t action;
  double execution_price = 0.00;
  int id = 0;
  double limit_price = 0.00;
  double max_profit = 0.00;
  int max_profit_timestamp = 0;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_PENDING;
  double stop_price = 0.00;
  const char *symbol;
  int timestamp = 0;
  order_type_t type;
};

struct position_t {
  order_t close_order;
  int close_timestamp = 0;
  order_t open_order;
};

struct quote_t {
  double current_price;
  double high;
  double low;
  char *symbol;
  long int timestamp;
};
} // namespace t
} // namespace ETrade
#endif
