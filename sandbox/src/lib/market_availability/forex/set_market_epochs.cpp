#ifndef MARKET_AVAILABILITY__FOREX_set_market_epochs
#define MARKET_AVAILABILITY__FOREX_set_market_epochs

#include "forex.h"                 // MarketAvailability::Forex
#include "get_close_epoch.cpp"     // get_close_epoch
#include "get_next_open_epoch.cpp" // get_next_open_epoch
#include "get_open_epoch.cpp"      // get_open_epoch
#include <string>                  // std::string

void MarketAvailability::Forex::set_market_epochs(
    const set_market_epochs_args_t args) {
  const double current_epoch = args.current_epoch;
  const double market_duration_hours = args.market_duration_hours;
  const std::string open_central_time = args.open_central_time;

  this->market_epochs.open = get_open_epoch({
      .current_epoch = current_epoch,
      .market_duration_hours = market_duration_hours,
      .open_central_time = open_central_time,
      .pending_open_epoch = current_epoch,
  });

  this->market_epochs.close = get_close_epoch({
      .market_duration_hours = market_duration_hours,
      .open_central_time = open_central_time,
      .open_epoch = this->market_epochs.open,
      .should_upper_bound = true,
  });

  this->market_epochs.next = get_next_open_epoch({
      .close_epoch = this->market_epochs.close,
      .market_duration_hours = market_duration_hours,
      .open_central_time = open_central_time,
  });
}

#endif
