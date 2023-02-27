#ifndef ALPACA__QUOTE_H
#define ALPACA__QUOTE_H

#include "alpaca/client/client.cpp" // Alpaca::Client
#include "alpaca/types.cpp"         // Alpaca::t
#include "lib/formatted.cpp"        // Formatted
#include "types.cpp"                // Global::t
#include <map>                      // std::map
#include <string>                   // std::string
#include <vector>                   // std::vector

namespace Alpaca {
class Quote {
public:
  Quote();

  void watch(const std::vector<std::string>);

private:
  using price_movement_t = Global::t::price_movement_t;
  using quote_t = Alpaca::t::quote_t;

  Alpaca::Client api_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  const double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  const int PRICE_MOVEMENT_SAMPLE_SIZE = 5e5;
  const int QUOTES_MAX_SIZE = 8e3;
  std::map<std::string, price_movement_t> price_movements;
  std::map<std::string, std::vector<quote_t>> quotes;

  double current_price(const std::string);

  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);
  quote_t read_streamed_quote(const std::string);

  void fetch_and_persist_quote(const std::string);
  void read(const std::string);
  void read_collection(const std::string);
  void set_and_persist_price_movement(const std::string);
  void set_price_movement(const std::string);
  void stream();
  void write();
  void write_collection(const std::string);
  void write_price_movement(const std::string);
};
} // namespace Alpaca

#endif
