#if !defined ETRADE__utils
#define ETRADE__utils

#include "etrade/constants.cpp" // ETrade::constants
#include "etrade/types.cpp"     // ETrade::t
#include "lib/formatted.cpp"    // Formatted::error_message
#include <stdexcept>            // std::invalid_argument
#include <string>               // std::string

namespace ETrade {
namespace utils {
ETrade::t::order_action_t to_order_action_t(const char *action) {
  int l = sizeof(ETrade::constants::ORDER_ACTIONS) /
          sizeof(*ETrade::constants::ORDER_ACTIONS);

  for (int i = 0; i < l; i++) {
    if (ETrade::constants::ORDER_ACTIONS[i] == std::string(action)) {
      return (order_action_t)i;
    }
  }

  std::string message = Formatted::error_message(
      std::string(action) + " is not a valid order action");

  throw std::invalid_argument(message);
}
} // namespace utils
} // namespace ETrade

#endif
