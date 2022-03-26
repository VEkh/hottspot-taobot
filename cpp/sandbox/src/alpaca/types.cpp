#ifndef ALPACA__types
#define ALPACA__types

#include <string> // std::string

namespace Alpaca {
namespace t {
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
  ORDER_PENDING_REPLACE,
  ORDER_REPLACED,
};

enum order_time_in_force_t {
  DAY,
};

enum order_type_t {
  MARKET,
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  double execution_price = 0.00;
  std::string id = "";
  double max_profit = 0.00;
  bool max_profit_reset = false;
  double profit = 0.00;
  double quantity = 0.00;
  order_status_t status = order_status_t::ORDER_INIT;
  const char *symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  int timestamp = 0;
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  order_t hedge_close_order;
  order_t hedge_open_order;
  order_t open_order;
};

struct quote_t {
  double ask = 0.00;
  double bid = 0.00;
  double price = 0.00;
  long int timestamp;
};
} // namespace t
} // namespace Alpaca
#endif
