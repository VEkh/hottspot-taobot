#ifndef ALPACA__CLIENT_set_market_open_epoch
#define ALPACA__CLIENT_set_market_open_epoch

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot
#include <string>             // std::string

void Alpaca::TaoBot::set_market_open_epoch() {
  const std::string iso_date =
      ::utils::time_::date_string(this->current_epoch, "%F", "America/Chicago");

  this->market_open_epoch = this->db_utils.timestamp_to_epoch(
      iso_date + " 08:30:00", "America/Chicago");
}

#endif
