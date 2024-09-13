#ifndef MARKET_AVAILABILITY__NYSE
#define MARKET_AVAILABILITY__NYSE

#include "nyse.h"           // MarketAvailability::Nyse, Base
#include "deps.cpp"         // json
#include "lib/pg/pg.cpp"    // Pg
#include "lib/utils/io.cpp" // ::utils::io
#include <list>             // std::list
#include <string>           // std::string

#include "is_early_close_day.cpp"
#include "is_market_open.cpp"

// Overrides
#include "is_market_day.cpp"
#include "next_market_open_epoch.cpp"
#include "set_market_epochs.cpp"

MarketAvailability::Nyse::Nyse(const Pg c) : Base(c, "nyse") {
  json early_closes_json =
      ::utils::io::read_file_to_json(this->data_dir + "/early_closes.json");

  std::list<std::string> early_closes_ = early_closes_json;

  this->early_closes = list_to_lookup(early_closes_);
}

#endif
