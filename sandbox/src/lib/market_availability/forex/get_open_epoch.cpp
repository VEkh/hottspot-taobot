#ifndef MARKET_AVAILABILITY__FOREX_get_open_epoch
#define MARKET_AVAILABILITY__FOREX_get_open_epoch

#include "epoch_at_time.cpp"   // epoch_at_time
#include "forex.h"             // MarketAvailability::Forex, market_weekdays_t
#include "get_close_epoch.cpp" // get_close_epoch
#include "lib/utils/time.cpp"  // ::utils::time_
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch
#include <algorithm>                   // std::max
#include <string>                      // std::string

double
MarketAvailability::Forex::get_open_epoch(const get_open_epoch_args_t args) {
  const double current_epoch = args.current_epoch;
  const double market_duration_hours = args.market_duration_hours;
  const std::string open_central_time = args.open_central_time;
  const double pending_open_epoch = args.pending_open_epoch;

  const double pending_open_epoch_ =
      current_epoch == pending_open_epoch
          ? epoch_at_time(pending_open_epoch, open_central_time)
          : pending_open_epoch;

  if (pending_open_epoch_ > current_epoch) {
    return get_open_epoch({
        .current_epoch = current_epoch,
        .market_duration_hours = market_duration_hours,
        .open_central_time = open_central_time,
        .pending_open_epoch = pending_open_epoch_ - this->ONE_DAY_SECONDS,
    });
  }

  const int pending_open_day_of_week =
      ::utils::time_::day_of_week(pending_open_epoch_);

  const double close_epoch = get_close_epoch({
      .market_duration_hours = market_duration_hours,
      .open_central_time = open_central_time,
      .open_epoch = pending_open_epoch_,
      .should_upper_bound =
          pending_open_day_of_week == market_weekdays_t::MARKET_WEEKDAY_END,
  });

  const double end_of_week_epoch = week_market_bound_epoch(
      current_epoch, market_weekdays_t::MARKET_WEEKDAY_END);

  const double start_of_week_epoch = week_market_bound_epoch(
      current_epoch, market_weekdays_t::MARKET_WEEKDAY_START);

  if (close_epoch > end_of_week_epoch) {
    return get_open_epoch({
        .current_epoch = current_epoch,
        .market_duration_hours = market_duration_hours,
        .open_central_time = open_central_time,
        .pending_open_epoch = std::max(
            start_of_week_epoch, pending_open_epoch_ - this->ONE_DAY_SECONDS),
    });
  }

  return pending_open_epoch_;
}

#endif
