#ifndef MARKET_AVAILABILITY__BASE_H
#define MARKET_AVAILABILITY__BASE_H

#include "db/utils/utils.cpp" // DB::Utils
#include "lib/pg/pg.cpp"      // Pg
#include "types.cpp"          // Global::t
#include <list>               // std::list
#include <map>                // std::map
#include <string>             // std::string

namespace MarketAvailability {
class Base {
public:
  using market_epochs_t = Global::t::market_epochs_t;

  Base(){};
  Base(const Pg, const std::string);

  market_epochs_t market_epochs;

  bool is_end_of_trading_period(const double);
  bool is_holiday(const double);

  virtual bool is_market_day(const double) { return false; };

  virtual double next_market_open_epoch(const double) { return 0.0; };

  virtual void set_market_epochs(const double){};

protected:
  DB::Utils db_utils;
  Pg conn;

  static constexpr int ONE_DAY_SECONDS = 24 * 60 * 60;

  std::map<std::string, bool> bad_data;
  std::map<std::string, bool> holidays;

  std::string data_dir;

  template <typename KeyType>
  std::map<KeyType, bool> list_to_lookup(const std::list<KeyType>);

  bool is_in_date_lookup(std::map<std::string, bool>, const double);

  virtual void set_market_close_epoch(const double){};
};
} // namespace MarketAvailability

#endif
