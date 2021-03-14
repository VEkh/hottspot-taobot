#if !defined ETRADE__utils
#define ETRADE__utils

#include "constants.cpp"     // ETrade::constants
#include "etrade/types.cpp"  // ETrade::t
#include "lib/formatted.cpp" // Formatted::error_message
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

namespace ETrade {
namespace utils {
ETrade::t::order_action_t to_order_action_t(const char *action) {
  int l = sizeof(ETrade::constants::ORDER_ACTIONS) /
          sizeof(*ETrade::constants::ORDER_ACTIONS);

  for (int i = 0; i < l; i++) {
    if (ETrade::constants::ORDER_ACTIONS[i] == std::string(action)) {
      return (ETrade::t::order_action_t)i;
    }
  }

  std::string message = Formatted::error_message(
      std::string(action) + " is not a valid order action");

  throw std::invalid_argument(message);
}

ETrade::t::order_status_t to_order_status_t(const std::string &status) {
  int l = sizeof(ETrade::constants::ORDER_STATUSES) /
          sizeof(*ETrade::constants::ORDER_STATUSES);

  for (int i = 0; i < l; i++) {
    if (ETrade::constants::ORDER_STATUSES[i] == status) {
      return (ETrade::t::order_status_t)i;
    }
  }

  std::string message =
      Formatted::error_message(std::string("❌ Status <" + status) +
                               "> was not present in ORDER_STATUSES.");

  std::cout << message << std::endl;

  exit(1);
}

} // namespace utils
} // namespace ETrade

#endif
