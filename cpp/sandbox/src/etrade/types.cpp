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

struct closed_positions_stats_t {
  std::map<order_win_result_t, int> results;
  double total_profit;
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

struct sma_t {
  double buy_delta = 0;
  double buy_sell_ratio = 0;
  double price = 0;
  int seconds = 0;
  double sell_buy_ratio = 0;
  double sell_delta = 0;
};

struct quote_t {
  double current_price;
  double high;
  double low;
  sma_t simple_moving_average;
  char *symbol;
  long int timestamp;
};
} // namespace t
} // namespace ETrade
#endif
