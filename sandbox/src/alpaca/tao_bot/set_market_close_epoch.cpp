#ifndef ALPACA__CLIENT_set_market_close_epoch
#define ALPACA__CLIENT_set_market_close_epoch

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // set_market_close_epoch
#include <string>             // std::string

void Alpaca::TaoBot::set_market_close_epoch() {
  const std::string iso_date =
      ::utils::time_::date_string(this->current_epoch, "%F", "America/Chicago");

  const std::string close_time =
      this->market_availability.is_early_close_day(this->current_epoch)
          ? " 12:00:00"
          : " 15:00:00";

  this->market_close_epoch = this->db_utils.timestamp_to_epoch(
      iso_date + close_time, "America/Chicago");
}

#endif
