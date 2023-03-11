#ifndef ALPACA__types
#define ALPACA__types

#include "src/types.cpp" // Global::t
#include <string>        // std::string

namespace Alpaca {
namespace t {
using order_win_result_streak_t = Global::t::order_win_result_streak_t;
using order_win_result_t = Global::t::order_win_result_t;
using quote_t = Global::t::quote_t;

enum order_action_t {
  BUY,
  SELL,
};

enum order_status_t {
  ORDER_ACCEPTED,
  ORDER_CANCELED,
  ORDER_DONE_FOR_DAY,
  ORDER_EXPIRED,
  ORDER_FILLED,
  ORDER_INIT,
  ORDER_NEW,
  ORDER_PARTIALLY_FILLED,
  ORDER_PENDING_CANCEL,
  ORDER_PENDING_NEW,
  ORDER_PENDING_REPLACE,
  ORDER_REPLACED,
};

enum order_time_in_force_t {
  DAY,
};

enum order_type_t {
  LIMIT,
  MARKET,
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  double execution_price = 0.00;
  std::string id = "";
  double limit_price = 0.00;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  long int max_profit_timestamp = 0;
  double profit = 0.00;
  double quantity = 0.00;
  order_status_t status = order_status_t::ORDER_INIT;
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  long int timestamp = 0;
  order_type_t type = order_type_t::MARKET;
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

struct position_t {
  order_t close_order;
  order_t open_order;
};

struct quote_scoreboard_t {
  quote_t quote;
  double score = 0.00;
  std::string type;
};
} // namespace t
} // namespace Alpaca
#endif
