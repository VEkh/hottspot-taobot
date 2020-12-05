#if !defined TD_AMERITRADE__STRADDLE_H
#define TD_AMERITRADE__STRADDLE_H

#include "lib/formatted.cpp"             // Formatted
#include "td_ameritrade/client/client.h" // TdAmeritrade::Client
#include "td_ameritrade/deps.cpp"        // json

namespace TdAmeritrade {
class Straddle {
public:
  Straddle(char *);
  Straddle(char *, int);

  void manual_run();
  void run();

private:
  struct prices_t {
    float close_limit;
    float open_stop;
    float open_stop_limit;
  };

  struct order_prices_t {
    prices_t buy;
    prices_t sell_short;
  } order_prices;

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  TdAmeritrade::Client td_ameritrade_client;
  char *symbol;
  int quantity;
  json original_quote;
  json quote;

  void fetch_current_quote();
  void log_start_message();
  void set_order_prices();
};
} // namespace TdAmeritrade

#endif
