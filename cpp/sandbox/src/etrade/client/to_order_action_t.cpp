#if !defined ETRADE__CLIENT_to_order_action_t
#define ETRADE__CLIENT_to_order_action_t

#include "client.h"          // ETrade::Client, ORDER_ACTIONS
#include "lib/formatted.cpp" // Formatted::error_message
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

ETrade::Client::order_action_t
ETrade::Client::to_order_action_t(const char *action) {
  int l = sizeof(ORDER_ACTIONS) / sizeof(*ORDER_ACTIONS);

  for (int i = 0; i < l; i++) {
    if (ORDER_ACTIONS[i] == std::string(action)) {
      return (order_action_t)i;
    }
  }

  std::string message = Formatted::error_message(
      std::string(action) + " is not a valid order action");

  throw std::invalid_argument(message);
}

#endif
