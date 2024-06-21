#ifndef ALPACA__utils
#define ALPACA__utils

#include "alpaca/types.cpp"   // Alpaca::t
#include "constants.cpp"      // Alpaca::constants
#include "lib/formatted.cpp"  // Formatted::error_message
#include "lib/utils/time.cpp" // ::utils::time_
#include <map>                // std::map
#include <stdexcept>          // std::invalid_argument
#include <string>             // std::string
#include <time.h>             // tm

namespace Alpaca {
namespace Utils {
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

bool is_early_close_day(const double epoch) {
  std::map<std::string, bool> DATES = {
      {"2023-07-03", true}, {"2023-11-24", true}, {"2024-07-03", true},
      {"2024-11-29", true}, {"2024-12-24", true},
  };

  const std::string date_string = ::utils::time_::date_string(epoch);

  return DATES[date_string];
}

bool is_end_of_trading_period(const double epoch) {
  if (is_early_close_day(epoch)) {
    return ::utils::time_::is_at_least(epoch,
                                       {
                                           .tm_sec = 0,
                                           .tm_min = 59,
                                           .tm_hour = 11,
                                       },
                                       "America/Chicago");
  }

  return ::utils::time_::is_at_least(epoch,
                                     {
                                         .tm_sec = 0,
                                         .tm_min = 59,
                                         .tm_hour = 14,
                                     },
                                     "America/Chicago");
}

bool is_holiday(const double epoch) {
  // TODO: Make separate BAD_DATA map and add 2022-03-15 to it
  std::map<std::string, bool> HOLIDAYS = {
      {"2022-01-17", true}, {"2022-03-15", true}, {"2022-04-15", true},
      {"2022-06-20", true}, {"2022-12-26", true}, {"2023-01-02", true},
      {"2023-01-16", true}, {"2023-02-20", true}, {"2023-04-07", true},
      {"2023-05-29", true}, {"2023-06-19", true}, {"2023-07-04", true},
      {"2023-09-04", true}, {"2023-11-23", true}, {"2023-12-25", true},
      {"2024-01-01", true}, {"2024-01-15", true}, {"2024-02-19", true},
      {"2024-03-29", true}, {"2024-05-27", true}, {"2024-06-19", true},
      {"2024-07-04", true}, {"2024-09-02", true}, {"2024-11-28", true},
      {"2024-12-25", true},
  };

  const std::string date_string = ::utils::time_::date_string(epoch);

  return HOLIDAYS[date_string];
}

bool is_market_day(const double epoch) {
  const int day_of_week_ = ::utils::time_::day_of_week(epoch);

  return day_of_week_ >= 1 && day_of_week_ <= 5;
}

bool is_market_open(const double epoch, const int late_start_seconds) {
  const int day_of_week_ = ::utils::time_::day_of_week(epoch);

  if (day_of_week_ < 1 || day_of_week_ > 5) {
    return false;
  }

  if (!is_market_day(epoch)) {
    return false;
  }

  if (is_holiday(epoch)) {
    return false;
  }

  if (is_end_of_trading_period(epoch)) {
    return false;
  }

  const tm market_open_time = {
      .tm_sec = late_start_seconds,
      .tm_min = 30,
      .tm_hour = 8,
  };

  return ::utils::time_::is_at_least(epoch, market_open_time,
                                     "America/Chicago") &&
         ::utils::time_::is_before(epoch,
                                   {
                                       .tm_sec = 0,
                                       .tm_min = 0,
                                       .tm_hour = 15,
                                   },
                                   "America/Chicago");
}

} // namespace Utils
} // namespace Alpaca

#endif
