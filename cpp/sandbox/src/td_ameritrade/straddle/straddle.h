#if !defined TD_AMERITRADE__STRADDLE_H
#define TD_AMERITRADE__STRADDLE_H

#include "lib/formatted.cpp"             // Formatted
#include "td_ameritrade/client/client.h" // TdAmeritrade::Client

namespace TdAmeritrade {
class Straddle {
public:
  Straddle(char *, int);

  void run();

private:
  int quantity;
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  char *symbol;
  TdAmeritrade::Client td_ameritrade_client;

  void fetch_current_quote();
  void log_start_message();
};
} // namespace TdAmeritrade

#endif
