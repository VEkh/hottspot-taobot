#if !defined ETRADE__STOCK_BOT_H
#define ETRADE__STOCK_BOT_H

#include "etrade/speedometer/speedometer.cpp" // ETrade::Speedometer
#include "etrade/types.cpp"                   // ETrade::t
#include "lib/formatted.cpp"                  // Formatted
#include <vector>                             // std::vector

using quote_t = ETrade::t::quote_t;
using sma_t = ETrade::t::sma_t;

namespace ETrade {
class StockBot {
public:
  void run();

  StockBot(char *, int);

private:
  const double POLLING_INTERVAL_SECONDS = 0.5;
  const double SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS = 5 * 60;

  char *symbol;
  int quantity;

  ETrade::Client etrade_client;
  ETrade::Speedometer speedometer = ETrade::Speedometer(&quotes);
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::vector<quote_t> quotes;

  quote_t parse_quote(const std::string &);

  sma_t simple_moving_average(const int);

  void fetch_quote();
  void initialize(char *, int);
  void log_quote();
  void log_simple_moving_average();
  void log_start_message();
  void watch();
};
} // namespace ETrade

#endif
