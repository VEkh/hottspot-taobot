#ifndef ETRADE__types
#define ETRADE__types

#include <map> // std::map

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
  MARKET,
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

struct order_t {
  order_action_t action;
  double execution_price = 0.00;
  int id = 0;
  double max_profit = 0.00;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_PENDING;
  const char *symbol;
  int timestamp = 0;
  order_type_t type;
};

struct position_t {
  order_t close_order;
  int close_timestamp = 0;
  order_t open_order;
};
} // namespace t
} // namespace ETrade
#endif
