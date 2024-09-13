#ifndef MARKET_AVAILABILITY__BASE
#define MARKET_AVAILABILITY__BASE

#include "base.h"             // MarketAvailability::Base
#include "deps.cpp"           // json
#include "lib/utils/io.cpp"   // ::utils::io
#include "list_to_lookup.cpp" // list_to_lookup
#include <list>               // std::list
#include <string>             // std::string

#include "is_end_of_trading_period.cpp"
#include "is_holiday.cpp"
#include "is_in_date_lookup.cpp"

MarketAvailability::Base::Base(const Pg conn, const std::string derived_class) {
  this->conn = conn;
  this->data_dir = std::string(APP_DIR) + "/src/lib/market_availability/" +
                   derived_class + "/data";

  json bad_data_json =
      ::utils::io::read_file_to_json(this->data_dir + "/bad_data.json");
  std::list<std::string> bad_data_ = bad_data_json;

  json holidays_json =
      ::utils::io::read_file_to_json(this->data_dir + "/holidays.json");
  std::list<std::string> holidays_ = holidays_json;

  this->bad_data = list_to_lookup(bad_data_);
  this->holidays = list_to_lookup(holidays_);

  this->db_utils = DB::Utils(this->conn);
}

#endif
