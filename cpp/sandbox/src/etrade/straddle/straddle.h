#if !defined ETRADE__STRADDLE_H
#define ETRADE__STRADDLE_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "lib/formatted.cpp"      // Formatted

namespace ETrade {
class Straddle {
public:
  struct prices_t {
    float close_limit;
    float close_stop;
    float close_stop_limit;
    float open_stop;
    float open_stop_limit;
  };

  Straddle(char *);
  Straddle(char *, int);

  void manual_run();
  void run();

private:
  struct order_prices_t {
    prices_t buy;
    prices_t sell_short;
  } order_prices;

  struct position_order_ids_t {
    int open_order_id;
    int profit_order_id;
    int stop_loss_order_id;
  };

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  char *symbol;
  int quantity;
  json original_quote;
  json quote;
  position_order_ids_t buy_position_order_ids;
  position_order_ids_t sell_short_position_order_ids;

  std::string build_place_order_payload(std::string);
  std::string build_preview_order_payload(const char *, prices_t);
  std::string compute_client_order_id();
  void log_manual_run_prices();
  void log_start_message();
  void open();
  void set_current_quote();
  void set_order_prices();
};
} // namespace ETrade

#endif
