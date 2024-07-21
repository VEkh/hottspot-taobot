#ifndef NYSE_AVAILABILITY
#define NYSE_AVAILABILITY

#include "nyse_availability.h" // NyseAvailability
#include "deps.cpp"            // json
#include "lib/utils/io.cpp"    // ::utils::io
#include "list_to_lookup.cpp"  // list_to_lookup
#include <list>                // std::list
#include <string>              // std::string

#include "is_early_close_day.cpp"
#include "is_end_of_trading_period.cpp"
#include "is_holiday.cpp"
#include "is_market_day.cpp"
#include "is_market_open.cpp"

NyseAvailability::NyseAvailability() {
  const std::string dir = std::string(APP_DIR) + "/src/lib/nyse_availability/";

  json bad_data_json = ::utils::io::read_file_to_json(dir + "bad_data.json");
  std::list<std::string> bad_data = bad_data_json;

  json early_closes_json =
      ::utils::io::read_file_to_json(dir + "early_closes.json");
  std::list<std::string> early_closes = early_closes_json;

  json holidays_json = ::utils::io::read_file_to_json(dir + "holidays.json");
  std::list<std::string> holidays = holidays_json;

  this->bad_data = list_to_lookup(bad_data);
  this->early_closes = list_to_lookup(early_closes);
  this->holidays = list_to_lookup(holidays);
}

#endif
