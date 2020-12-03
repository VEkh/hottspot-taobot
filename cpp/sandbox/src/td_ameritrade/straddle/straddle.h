#if !defined TD_AMERITRADE__STRADDLE_H
#define TD_AMERITRADE__STRADDLE_H

#include "lib/formatted.cpp"             // Formatted
#include "td_ameritrade/client/client.h" // TdAmeritrade::Client
#include "td_ameritrade/deps.cpp"        // simdjson
#include <string>                        // std::string

namespace TdAmeritrade {
class Straddle {
public:
  Straddle(char *, int);

  void run();

private:
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  TdAmeritrade::Client td_ameritrade_client;
  char *symbol;
  int quantity;
  simdjson::dom::parser json_parser;
  std::string quote;

  std::string condensed_quote();
  void fetch_current_quote();
  void log_start_message();
};
} // namespace TdAmeritrade

#endif
