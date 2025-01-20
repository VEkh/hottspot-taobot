#ifndef ALPACA__types
#define ALPACA__types

#include "src/types.cpp" // Global::t
#include <math.h>        // INFINITY
#include <string>        // std::string

namespace Alpaca {
namespace t {
using candle_t = Global::t::candle_t; // TODO: Decide
using order_action_t = Global::t::order_action_t;
using order_win_result_t = Global::t::order_win_result_t;
using order_type_t = Global::t::order_type_t;
using reversal_t = Global::t::reversal_t;
using quote_t = Global::t::quote_t;
using trend_meta_t = Global::t::trend_meta_t;
using trend_t = Global::t::trend_t;

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
  ORDER_REJECTED,
  ORDER_REPLACED,
};

enum order_time_in_force_t {
  DAY,
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  candle_t day_candle; // TODO: Decide
  reversal_t entry_reversal;
  double execution_price = 0.00;
  std::string id = "";
  double limit_price = 0.00;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  double max_profit_at = 0;
  double min_profit = 0.00;
  double min_profit_at = 0;
  double profit = 0.00;
  double quantity = 0.00;
  order_status_t status = order_status_t::ORDER_INIT;
  double stop_loss = 0.00;
  double stop_profit = 0.00;
  reversal_t stop_profit_reversal;
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  double timestamp = 0;
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  order_t open_order;
};
} // namespace t
} // namespace Alpaca
#endif
