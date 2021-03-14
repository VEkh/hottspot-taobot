#if !defined ETRADE__STOCK_BOT_H
#define ETRADE__STOCK_BOT_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "etrade/types.cpp"       // ETrade::t
#include "lib/formatted.cpp"      // Formatted
#include <map>                    // std::map
#include <vector>                 // std::vector

namespace ETrade {
class StockBot {
public:
  void run();

  StockBot(char *, int);

private:
  using order_action_t = ETrade::t::order_action_t;
  using order_status_t = ETrade::t::order_status_t;
  using order_t = ETrade::t::order_t;
  using order_type_t = ETrade::t::order_type_t;
  using quote_t = ETrade::t::quote_t;
  using sma_t = ETrade::t::sma_t;

  const double POLLING_INTERVAL_SECONDS = 0.5;
  const double SIMPLE_MOVING_AVERAGE_PERIOD_SECONDS = 5 * 60;

  std::map<const char *, const char *> ICONS = {
      {"BUY", "📈"},
      {"SELL_SHORT", "📉"},
  };

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  char *symbol;
  int quantity;
  json placed_orders;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  std::vector<quote_t> quotes;

  bool is_long_side(const order_t *);
  bool should_open_position();
  json get_order_json(const order_t *);
  quote_t parse_quote(const std::string &);
  sma_t simple_moving_average(const int);
  void fetch_orders();
  void fetch_quote();
  void initialize(char *, int);
  void log_open_position();
  void log_quote();
  void log_simple_moving_average();
  void log_start_message();
  void open_position();
  void set_execution_price(order_t *);
  void set_open_position_prices();
  void set_position_status();
  void set_profit(order_t *);
  void set_profit(order_t *, const order_t *);
  void set_status(order_t *);
  void watch();
};
} // namespace ETrade

#endif
