#if !defined ETRADE__STRADDLE_H
#define ETRADE__STRADDLE_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "lib/formatted.cpp"      // Formatted
#include <vector>                 // std::vector

using order_action_t = ETrade::Client::order_action_t;
using order_status_t = ETrade::Client::order_status_t;
using order_t = ETrade::Client::order_t;
using order_type_t = ETrade::Client::order_type_t;

namespace ETrade {
class Straddle {
public:
  enum status_t {
    CLOSED,
    COMPLETE,
    LIMBO,
    OPEN,
    PENDING,
  };

  Straddle(char *);
  Straddle(char *, int);

  void manual_run();
  void run();

private:
  struct odometer_t {
    std::vector<double> accelerations;
    double momentum = 0.00;
    std::vector<double> velocities;
  } odometer;

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  char *symbol;
  int POLLING_INTERVAL_SECONDS = 5;
  int day_range;
  int quantity;

  json placed_orders;
  json quote;

  order_t buy_open_order;
  order_t buy_profit_order;
  order_t sell_short_open_order;
  order_t sell_short_profit_order;

  json get_order_json(const order_t &);

  status_t status();

  double compute_odometer_average(const std::vector<double> &, const int);

  void fetch_and_set_orders();
  void fetch_and_set_quote();
  void log_order_statuses();
  void log_odometer();
  void log_prices();
  void log_start_message();
  void log_status();
  void odometer_tick(const double &, const double &);
  void open();
  void set_order_prices();
  void set_execution_price(order_t &);
  void set_profit(order_t &);
  void set_status(order_t &);
  void set_trailing_stop_price(order_t &, const order_t &);
  void watch();
  void watch_buy();
  void watch_sell_short();
};
} // namespace ETrade

#endif
