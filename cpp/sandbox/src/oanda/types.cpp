#ifndef OANDA__types
#define OANDA__types

namespace Oanda {
namespace t {
enum order_action_t {
  BUY,
  SELL,
};

enum order_status_t {
  ORDER_CANCELLED,
  ORDER_FILLED,
  ORDER_PENDING,
  ORDER_TRIGGERED,
};

enum order_type_t {
  MARKET,
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
} // namespace Oanda
#endif
