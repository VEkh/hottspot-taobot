#ifndef ALPACA__types
#define ALPACA__types

#include "src/types.cpp" // Global::t
#include <math.h>        // INFINITY
#include <string>        // std::string

namespace Alpaca {
namespace t {
using order_action_t = Global::t::order_action_t;
using order_win_result_t = Global::t::order_win_result_t;
using quote_t = Global::t::quote_t;

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

enum order_type_t {
  LIMIT,
  MARKET,
};

// TODO: Decide
struct range_t {
  double closed_at = 0;
  double high = -INFINITY;
  double low = INFINITY;
  double lower_mid = 0;
  double mid = 0;
  double opened_at = 0;
  double upper_mid = 0;

  double delta() { return this->high - this->low; }
};

// TODO: Decide
enum reversal_type_t {
  REVERSAL_HIGH,
  REVERSAL_LOW,
};

struct reversal_t {
  double at;
  bool is_record;
  double mid;
  reversal_type_t type;
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  range_t consolidation_range; // TODO: Decide
  double execution_price = 0.00;
  std::string id = "";
  bool is_loss_reversal = false; // TODO: Decide
  double limit_price = 0.00;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  double max_profit_at = 0;
  double min_profit = 0.00;
  double min_profit_at = 0;
  double profit = 0.00;
  double quantity = 0.00;
  reversal_t reversal;
  order_status_t status = order_status_t::ORDER_INIT;
  double stop_loss = 0.00;
  double stop_profit = 0.00;
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
