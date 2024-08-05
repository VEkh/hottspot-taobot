#ifndef NYSE_AVAILABILITY_H
#define NYSE_AVAILABILITY_H

#include "db/utils/utils.cpp" // DB::Utils
#include "lib/pg/pg.cpp"      // Pg
#include <list>               // std::list
#include <map>                // std::map
#include <string>             // std::string

class NyseAvailability {
public:
  NyseAvailability(const Pg);
  NyseAvailability(){};

  bool is_early_close_day(const double);
  bool is_end_of_trading_period(const double);
  bool is_holiday(const double);
  bool is_market_day(const double);
  bool is_market_open(const double, const int);

  double market_close_epoch(const double);
  double market_open_epoch(const double);

private:
  DB::Utils db_utils;
  Pg conn;

  std::map<std::string, bool> bad_data;
  std::map<std::string, bool> early_closes;
  std::map<std::string, bool> holidays;

  template <typename KeyType>
  std::map<KeyType, bool> list_to_lookup(const std::list<KeyType>);

  bool is_in_date_lookup(std::map<std::string, bool>, const double);
  bool is_market_day_of_week(const double);
};

#endif
