#ifndef MARKET_AVAILABILITY__FOREX_get_next_open_epoch
#define MARKET_AVAILABILITY__FOREX_get_next_open_epoch

#include "forex.h"                     // MarketAvailability::Forex
#include "week_market_bound_epoch.cpp" // week_market_bound_epoch
#include <algorithm>                   // std::max, std::min
#include <string>                      // std::string

double MarketAvailability::Forex::get_next_open_epoch(
    const get_next_open_epoch_args_t args) {
  const double close_epoch = args.close_epoch;
  const double market_duration_hours = args.market_duration_hours;
  const std::string open_central_time = args.open_central_time;

  const double current_week_end = week_market_bound_epoch(
      this->market_epochs.open, market_weekdays_t::MARKET_WEEKDAY_END);

  const double current_week_start = week_market_bound_epoch(
      this->market_epochs.open, market_weekdays_t::MARKET_WEEKDAY_START);

  const double next_week_end =
      week_market_bound_epoch(this->market_epochs.open + this->ONE_WEEK_SECONDS,
                              market_weekdays_t::MARKET_WEEKDAY_END);

  const double next_week_start =
      week_market_bound_epoch(this->market_epochs.open + this->ONE_WEEK_SECONDS,
                              market_weekdays_t::MARKET_WEEKDAY_START);

  double next_open = epoch_at_time(this->market_epochs.open, open_central_time);

  next_open += std::max((double)this->ONE_DAY_SECONDS,
                        market_duration_hours * this->ONE_HOUR_SECONDS);

  bool is_next_open_valid = false;

  while (!is_next_open_valid) {
    if (next_open < this->market_epochs.close) {
      next_open += this->ONE_DAY_SECONDS;
      continue;
    }

    if (!(next_open >= current_week_start && next_open < current_week_end) &&
        !(next_open >= next_week_start && next_open < next_week_end)) {
      next_open += this->ONE_DAY_SECONDS;
      continue;
    }

    is_next_open_valid = true;
  }

  const double now = time(nullptr);

  return std::min(now, next_open);
}
#endif
