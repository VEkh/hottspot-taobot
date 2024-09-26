#ifndef OANDA__types
#define OANDA__types

#include "src/types.cpp" // Global::t

namespace Oanda {
namespace t {
using order_action_t = Global::t::order_action_t;
using order_type_t = Global::t::order_type_t;
using quote_t = Global::t::quote_t;
using reversal_t = Global::t::reversal_t;

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

enum trade_status_t {
  TRADE_CLOSED,
  TRADE_OPEN,
};

struct order_t {
  order_action_t action;
  reversal_t entry_reversal;
  double execution_price = 0.00;
  int id = 0;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  double max_profit_at = 0;
  double min_profit = 0.00;
  double min_profit_at = 0;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_INIT;
  double stop_loss = 0.00;
  double stop_profit = 0.00;
  reversal_t stop_profit_reversal;
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::FOK;
  double timestamp = 0;
  int trade_id = 0;
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  order_t open_order;
};
} // namespace t
} // namespace Oanda
#endif
