#if !defined ETRADE__STRADDLE_H
#define ETRADE__STRADDLE_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "lib/formatted.cpp"      // Formatted

namespace ETrade {
class Straddle {
public:
  Straddle(char *);
  Straddle(char *, int);

  void manual_run();
  void run();

private:
  struct prices_t {
    float close_limit;
    float close_stop;
    float close_stop_limit;
    float open_stop;
    float open_stop_limit;
  };

  struct order_prices_t {
    prices_t buy;
    prices_t sell_short;
  } order_prices;

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  ETrade::Client etrade_client;
  char *symbol;
  int quantity;
  json original_quote;
  json quote;

  json build_order_open_payload(const char *, prices_t);
  void log_manual_run_prices();
  void log_start_message();
  void open_straddle();
  void set_current_quote();
  void set_order_prices();
};
} // namespace ETrade

#endif
