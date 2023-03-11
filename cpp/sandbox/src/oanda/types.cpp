#ifndef OANDA__types
#define OANDA__types

#include "src/types.cpp" // Global::t

namespace Oanda {
namespace t {
using quote_t = Global::t::quote_t;

enum order_action_t {
  BUY,
  SELL,
};

enum order_status_t {
  ORDER_CANCELLED,
  ORDER_FILLED,
  ORDER_INIT,
  ORDER_PENDING,
  ORDER_TRIGGERED,
};

enum order_time_in_force_t {
  FOK,
  GTC,
};

enum order_type_t {
  LIMIT,
  MARKET,
};

enum trade_status_t {
  TRADE_CLOSED,
  TRADE_OPEN,
};

struct order_t {
  order_action_t action;
  double execution_price = 0.00;
  int id = 0;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  long int max_profit_timestamp = 0;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_INIT;
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::FOK;
  long int timestamp = 0;
  int trade_id = 0;
  order_type_t type;
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
} // namespace Oanda
#endif
