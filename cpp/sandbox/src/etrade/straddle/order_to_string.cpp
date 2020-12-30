#if !defined ETRADE__STRADDLE_order_to_string
#define ETRADE__STRADDLE_order_to_string

/*
 * ETrade::Straddle
 * ORDER_ACTIONS
 * ORDER_STATUSES
 * ORDER_TYPES
 * order_t
 * symbol
 */
#include "straddle.h"

#include "etrade/deps.cpp" // json
#include <string>          // std::string

std::string ETrade::Straddle::order_to_string(const order_t &order) {
  json collection = {
      {"action", ORDER_ACTIONS[order.action]},
      {"id", order.id},
      {"limit_price", order.limit_price},
      {"status", ORDER_STATUSES[order.status]},
      {"symbol", symbol},
      {"type", ORDER_TYPES[order.type]},
  };

  if (order.stop_price) {
    collection["stop_price"] = order.stop_price;
  }

  return collection.dump();
}

#endif
