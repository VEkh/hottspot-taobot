#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "lib/formatted.cpp"       // Formatted
#include "oanda/client/client.cpp" // Oanda::Client
#include "oanda/types.cpp"         // Oanda::t
#include "types.cpp"               // Global::t
#include <list>                    // std::list
#include <map>                     // std::map
#include <string>                  // std::string

namespace Oanda {
class TaoBot {
public:
  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using candlestick_t = Global::t::candlestick_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;
  using quote_t = Global::t::quote_t;

  const double POLLING_INTERVAL_SECONDS = 1.0;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  char *symbol;
  int quantity;
  order_t *close_order_ptr = nullptr;
  order_t close_order;
  std::list<candlestick_t> candlesticks;
  std::vector<quote_t> quotes;

  bool is_end_of_trading_period();
  bool is_market_open();
  bool should_terminate();

  void await_market_open();
  void build_candlesticks();
  void initialize(char *, std::map<std::string, std::string> &);
  void fetch_quote();
  void log_candlesticks();
  void log_quote();
  void log_start_message();
  void watch();
};
} // namespace Oanda

#endif
