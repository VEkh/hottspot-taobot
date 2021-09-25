#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "lib/formatted.cpp" // Formatted
#include "oanda/types.cpp"   // Oanda::t
#include <map>               // std::map
#include <string>            // std::string

namespace Oanda {
class TaoBot {
public:
  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;

  const double POLLING_INTERVAL_SECONDS = 1.0;

  char *symbol;
  int quantity;
  order_t *close_order_ptr = nullptr;
  order_t close_order;

  Formatted::fmt_stream_t fmt = Formatted::stream();

  bool is_end_of_trading_period();
  bool is_market_open();
  bool should_terminate();

  void await_market_open();
  void initialize(char *, std::map<std::string, std::string> &);
  void log_start_message();
  void watch();
};
} // namespace Oanda

#endif
