#ifndef MARKET_AVAILABILITY__NYSE_H
#define MARKET_AVAILABILITY__NYSE_H

#include "lib/market_availability/base/base.cpp" // MarketAvailability::Base
#include "lib/pg/pg.cpp"                         // Pg

namespace MarketAvailability {
using Base = MarketAvailability::Base;

class Nyse : public Base {
public:
  Nyse(){};
  Nyse(const Pg c);

  bool is_early_close_day(const double);
  bool is_market_day(const double) override;
  bool is_market_open(const double, const bool);

  double next_market_open_epoch(const double) override;

  void set_market_epochs(const double) override;

private:
  std::map<std::string, bool> early_closes;

  bool is_market_day_of_week(const double);

  double get_market_open_epoch(const double, const int);

  void set_market_close_epoch(const double) override;
  void set_market_open_epoch(const double, const int);
};
} // namespace MarketAvailability

#endif
