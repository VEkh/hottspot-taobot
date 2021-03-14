#if !defined ETRADE__types
#define ETRADE__types

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

struct order_t {
  order_action_t action;
  double execution_price = 0.00;
  int id = 0;
  double limit_price = 0.00;
  double profit = 0.00;
  int quantity;
  order_status_t status = order_status_t::ORDER_PENDING;
  double stop_price = 0.00;
  const char *symbol;
  order_type_t type;
};

struct sma_t {
  double buy_delta = 0.00;
  double price;
  int seconds = 0;
  double sell_delta = 0.00;
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
