#ifndef FOREX_AVAILABILITY
#define FOREX_AVAILABILITY

#include "forex_availability.h" // ForexAvailability
#include "deps.cpp"             // json
#include "lib/utils/io.cpp"     // ::utils::io
#include "list_to_lookup.cpp"   // list_to_lookup
#include <list>                 // std::list
#include <string>               // std::string

#include "is_end_of_trading_period.cpp"
#include "is_holiday.cpp"
#include "is_market_open.cpp"
#include "set_market_close_epoch.cpp"
#include "set_market_open_epoch.cpp"

ForexAvailability::ForexAvailability(const Pg conn) {
  this->conn = conn;

  const std::string dir =
      std::string(APP_DIR) + "/src/lib/forex_availability/data";

  json bad_data_json = ::utils::io::read_file_to_json(dir + "/bad_data.json");
  std::list<std::string> bad_data_ = bad_data_json;

  json early_closes_json =
      ::utils::io::read_file_to_json(dir + "/early_closes.json");
  std::list<std::string> early_closes_ = early_closes_json;

  json holidays_json = ::utils::io::read_file_to_json(dir + "/holidays.json");
  std::list<std::string> holidays_ = holidays_json;

  this->bad_data = list_to_lookup(bad_data_);
  this->early_closes = list_to_lookup(early_closes_);
  this->holidays = list_to_lookup(holidays_);

  this->db_utils = DB::Utils(this->conn);
}

#endif
