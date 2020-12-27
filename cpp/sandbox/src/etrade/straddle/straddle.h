#if !defined ETRADE__STRADDLE_H
#define ETRADE__STRADDLE_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "lib/formatted.cpp"      // Formatted

namespace ETrade {
class Straddle {
public:
  enum order_action_t {
    BUY,
    BUY_TO_COVER,
    SELL,
    SELL_SHORT,
  };

  enum order_status_t {
    ORDER_CANCELLED,
    ORDER_EXECUTED,
    ORDER_OPEN,
  };

  enum order_type_t {
    LIMIT,
    STOP_LIMIT,
  };

  enum status_t {
    CLOSED,
    COMPLETE,
    OPEN,
    PENDING,
  };

  struct order_t {
    order_action_t action;
    int id;
    double limit_price;
    order_status_t status;
    double stop_price;
    order_type_t type;
  };

  const char *ORDER_STATUSES[3] = {
      "CANCELLED",
      "EXECUTED",
      "OPEN",
  };

  Straddle(char *);
  Straddle(char *, int);

  void manual_run();
  void run();

private:
  const char *ORDER_ACTIONS[4] = {
      "BUY",
      "BUY_TO_COVER",
      "SELL",
      "SELL_SHORT",
  };

  const char *ORDER_TYPES[2] = {
      "LIMIT",
      "STOP_LIMIT",
  };

  ETrade::Client etrade_client;
  Formatted::fmt_stream_t stream_format = Formatted::stream();
  char *symbol;
  int quantity;

  json original_quote;
  json quote;

  order_t buy_open_order;
  order_t buy_profit_order;
  order_t buy_stop_loss_order;
  order_t sell_short_open_order;
  order_t sell_short_profit_order;
  order_t sell_short_stop_loss_order;

  status_t status();
  std::string build_place_order_payload(std::string);
  std::string build_preview_order_payload(order_t);
  std::string compute_client_order_id(std::string);
  void log_manual_run_prices();
  void log_start_message();
  void open();
  void set_current_quote();
  void set_order_prices();
};
} // namespace ETrade

#endif
