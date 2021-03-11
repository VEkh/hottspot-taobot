#if !defined ETRADE__STOCK_BOT_BETA_H
#define ETRADE__STOCK_BOT_BETA_H

#include "etrade/deps.cpp"   // json, _json
#include "lib/formatted.cpp" // Formatted
#include <vector>            // std::vector

namespace ETrade {
class StockBotBeta {
public:
  void run();

  StockBotBeta(char *, int);

private:
  const double POLLING_INTERVAL_SECONDS = 0.5;

  struct quote_t {
    double current_price;
    double high;
    double low;
    double simple_moving_average;
    char *symbol;
    long int timestamp;
  };

  char *symbol;
  int quantity;

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::vector<quote_t> quotes;

  quote_t parse_quote(const std::string &);

  void fetch_quote();
  void initialize(char *, int);
  void log_quote();
  void log_start_message();
  void watch();
};
} // namespace ETrade

#endif
