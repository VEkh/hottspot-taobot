#ifndef MARKET_AVAILABILITY__FOREX_H
#define MARKET_AVAILABILITY__FOREX_H

#include "lib/market_availability/base/base.cpp" // MarketAvailability::Base
#include "lib/pg/pg.cpp"                         // Pg

namespace MarketAvailability {
using Base = MarketAvailability::Base;

class Forex : public Base {
public:
  Forex(){};
  Forex(const Pg c) : Base(c, "forex"){};

  bool is_market_day(const double) override;
  bool is_market_open(const double);

  double next_market_open_epoch(const double) override;

  void set_market_epochs(const double) override;

private:
  std::map<std::string, bool> early_closes;

  bool is_market_day_of_week(const double);

  double get_market_open_epoch(const double);

  void set_market_close_epoch(const double) override;
  void set_market_open_epoch(const double);
};
} // namespace MarketAvailability

#endif