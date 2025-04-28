#ifndef MARKET_AVAILABILITY__FOREX_H
#define MARKET_AVAILABILITY__FOREX_H

#include "lib/market_availability/base/base.cpp" // MarketAvailability::Base
#include "lib/pg/pg.cpp"                         // Pg
#include <string>                                // std::string

namespace MarketAvailability {
using Base = MarketAvailability::Base;

class Forex : public Base {
public:
  Forex(){};
  Forex(const Pg c) : Base(c, "forex"){};

  struct set_market_epochs_args_t {
    double current_epoch = 0.0;
    double market_duration_hours = 0.0;
    std::string open_central_time;
  };

  bool is_market_day(const double) override;
  bool is_market_open(const double);

  void set_market_epochs(const set_market_epochs_args_t);

private:
  enum market_weekdays_t {
    MARKET_WEEKDAY_END = 5,
    MARKET_WEEKDAY_SATURDAY = 6,
    MARKET_WEEKDAY_START = 0,
  };

  struct get_close_epoch_args_t {
    double market_duration_hours = 0.0;
    std::string open_central_time;
    double open_epoch = 0.0;
    bool should_upper_bound = true;
  };

  struct get_next_open_epoch_args_t {
    double close_epoch = 0.0;
    double market_duration_hours = 0.0;
    std::string open_central_time;
  };

  struct get_open_epoch_args_t {
    double current_epoch = 0.0;
    double market_duration_hours = 0.0;
    std::string open_central_time;
    double pending_open_epoch = 0.0;
  };

  static constexpr int ONE_DAY_HOURS = 24;
  static constexpr int ONE_HOUR_SECONDS = 60 * 60;
  static constexpr int ONE_WEEK_SECONDS = ONE_DAY_HOURS * 7 * ONE_HOUR_SECONDS;

  std::map<std::string, bool> early_closes;

  bool is_market_day_of_week(const double);

  double epoch_at_time(const double, const std::string);
  double get_close_epoch(const get_close_epoch_args_t);
  double get_next_open_epoch(const get_next_open_epoch_args_t);
  double get_open_epoch(const get_open_epoch_args_t);
  double week_market_bound_epoch(const double epoch, const market_weekdays_t);
};
} // namespace MarketAvailability

#endif
