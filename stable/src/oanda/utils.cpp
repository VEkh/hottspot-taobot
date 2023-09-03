#ifndef OANDA__utils
#define OANDA__utils

#include "constants.cpp"     // Oanda::constants
#include "lib/formatted.cpp" // Formatted::error_message
#include "oanda/types.cpp"   // Oanda::t, order_status_t
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string

namespace Oanda {
namespace utils {
Oanda::t::order_action_t to_order_action_t(const char *action) {
  int l = sizeof(Oanda::constants::ORDER_ACTIONS) /
          sizeof(*Oanda::constants::ORDER_ACTIONS);

  for (int i = 0; i < l; i++) {
    if (Oanda::constants::ORDER_ACTIONS[i] == std::string(action)) {
      return (Oanda::t::order_action_t)i;
    }
  }

  std::string message = Formatted::error_message(
      std::string(action) + " is not a valid order action");

  throw std::invalid_argument(message);
}

Oanda::t::order_status_t to_order_status_t(const std::string &status) {
  int l = sizeof(Oanda::constants::ORDER_STATUSES) /
          sizeof(*Oanda::constants::ORDER_STATUSES);

  for (int i = 0; i < l; i++) {
    if (Oanda::constants::ORDER_STATUSES[i] == status) {
      return (Oanda::t::order_status_t)i;
    }
  }

  std::string message =
      Formatted::error_message(std::string("❌ Status <" + status) +
                               "> was not present in ORDER_STATUSES.");

  std::cout << message << std::endl;

  exit(1);
}

Oanda::t::trade_status_t to_trade_status_t(const std::string &status) {
  int l = sizeof(Oanda::constants::TRADE_STATUSES) /
          sizeof(*Oanda::constants::TRADE_STATUSES);

  for (int i = 0; i < l; i++) {
    if (Oanda::constants::TRADE_STATUSES[i] == status) {
      return (Oanda::t::trade_status_t)i;
    }
  }

  std::string message =
      Formatted::error_message(std::string("❌ Status <" + status) +
                               "> was not present in TRADE_STATUSES.");

  std::cout << message << std::endl;

  exit(1);
}

Oanda::t::order_status_t
trade_status_to_order_status_t(const std::string &status) {
  int l = sizeof(Oanda::constants::TRADE_STATUSES) /
          sizeof(*Oanda::constants::TRADE_STATUSES);

  for (int i = 0; i < l; i++) {
    if (Oanda::constants::TRADE_STATUSES[i] == status) {
      return Oanda::t::order_status_t::ORDER_FILLED;
    }
  }

  return Oanda::t::order_status_t::ORDER_PENDING;
}

} // namespace utils
} // namespace Oanda

#endif
