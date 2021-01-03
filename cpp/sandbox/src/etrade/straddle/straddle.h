#if !defined ETRADE__STRADDLE_H
#define ETRADE__STRADDLE_H

#include "etrade/client/client.h" // ETrade::Client
#include "etrade/deps.cpp"        // json
#include "lib/formatted.cpp"      // Formatted

#include <vector>

namespace ETrade {
class Straddle {
public:
  static constexpr const char *ORDER_STATUSES[] = {
      "CANCELLED",
      "EXECUTED",
      "OPEN",
      "PENDING",
  };

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
    ORDER_PENDING,
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
    int id = 0;
    double limit_price = 0.00;
    order_status_t status = order_status_t::ORDER_PENDING;
    double stop_price = 0.00;
    order_type_t type;
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
  json placed_orders;
  json quote;

  order_t buy_open_order;
  order_t buy_profit_order;
  order_t buy_stop_loss_order;
  order_t sell_short_open_order;
  order_t sell_short_profit_order;
  order_t sell_short_stop_loss_order;

  CurlClient cancel_order(order_t &);
  CurlClient handle_request_error(const CurlClient &, const order_action_t &,
                                  const std::string &);
  CurlClient place_order(order_t &);
  CurlClient preview_order(const order_t &);

  order_status_t get_order_status(const order_t &);

  status_t status();

  std::string build_place_order_payload(std::string &);
  std::string build_preview_order_payload(const order_t &);
  std::string compute_client_order_id(const std::string);
  std::string order_to_string(const order_t &);

  void fetch_and_set_orders();
  void fetch_and_set_quote();
  void log_order_statuses();
  void log_prices();
  void log_start_message();
  void open();
  void set_order_prices();
  void watch();
  void watch_buy();
  void watch_sell_short();
};
} // namespace ETrade

#endif
