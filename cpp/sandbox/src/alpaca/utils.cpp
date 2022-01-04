#ifndef ALPACA__utils
#define ALPACA__utils

#include "alpaca/types.cpp"  // Alpaca::t
#include "constants.cpp"     // Alpaca::constants
#include "lib/formatted.cpp" // Formatted::error_message
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

namespace Alpaca {
namespace utils {
Alpaca::t::order_action_t to_order_action_t(const char *action) {
  int l = sizeof(Alpaca::constants::ORDER_ACTIONS) /
          sizeof(*Alpaca::constants::ORDER_ACTIONS);

  for (int i = 0; i < l; i++) {
    if (Alpaca::constants::ORDER_ACTIONS[i] == std::string(action)) {
      return (Alpaca::t::order_action_t)i;
    }
  }

  std::string message = Formatted::error_message(
      std::string(action) + " is not a valid order action");

  throw std::invalid_argument(message);
}

Alpaca::t::order_status_t to_order_status_t(const std::string &status) {
  int l = sizeof(Alpaca::constants::ORDER_STATUSES) /
          sizeof(*Alpaca::constants::ORDER_STATUSES);

  for (int i = 0; i < l; i++) {
    if (Alpaca::constants::ORDER_STATUSES[i] == status) {
      return (Alpaca::t::order_status_t)i;
    }
  }

  std::string message =
      Formatted::error_message(std::string("❌ Status <" + status) +
                               "> was not present in ORDER_STATUSES.");

  std::cout << message << std::endl;

  exit(1);
}

} // namespace utils
} // namespace Alpaca

#endif
