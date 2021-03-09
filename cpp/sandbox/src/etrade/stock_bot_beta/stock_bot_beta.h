#if !defined ETRADE__STOCK_BOT_BETA_H
#define ETRADE__STOCK_BOT_BETA_H

#include "etrade/deps.cpp"   // json, _json
#include "lib/formatted.cpp" // Formatted

namespace ETrade {
class StockBotBeta {
public:
  void run();

  StockBotBeta(char *, int);

private:
  const double POLLING_INTERVAL_SECONDS = 0.5;

  char *symbol;
  int quantity;

  ETrade::Client etrade_client;

  Formatted::fmt_stream_t fmt = Formatted::stream();

  json quotes = R"([])"_json;

  void fetch_and_set_quote();
  void initialize(char *, int);
  void log_start_message();
  void watch();
};
} // namespace ETrade

#endif
