#ifndef ALPACA__types
#define ALPACA__types

#include "src/types.cpp" // Global::t
#include <string>        // std::string

namespace Alpaca {
namespace t {
using order_win_result_t = Global::t::order_win_result_t;
using quote_t = Global::t::quote_t;

struct account_exit_prices_t {
  double current_profit = 0.00;
  double max_profit = 0.00;
  double stop_profit_loss = 0.00;
  double target_account_profit = 0.00;
  double target_max_profit = 0.00;
};

struct account_snapshot_t {
  double equity = 0.00;
  double margin_buying_power = 0.00;
  double margin_multiplier = 0.00;
  double max_equity = 0.00;
  double max_equity_timestamp = 0;
  double min_equity = 0.00;
  double min_equity_timestamp = 0;
  double original_equity = 0.00;
  double original_margin_buying_power = 0.00;
  double timestamp = 0;
  std::string api_key_id = "";
};

enum order_action_t {
  BUY,
  SELL,
};

enum order_status_t {
  ORDER_ACCEPTED,
  ORDER_CANCELED,
  ORDER_DONE_FOR_DAY,
  ORDER_EXPIRED,
  ORDER_FILLED,
  ORDER_INIT,
  ORDER_NEW,
  ORDER_PARTIALLY_FILLED,
  ORDER_PENDING_CANCEL,
  ORDER_PENDING_NEW,
  ORDER_PENDING_REPLACE,
  ORDER_REPLACED,
};

enum order_time_in_force_t {
  DAY,
};

enum order_type_t {
  LIMIT,
  MARKET,
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  double execution_price = 0.00;
  std::string id = "";
  double limit_price = 0.00;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  double max_profit_timestamp = 0;
  double profit = 0.00;
  double quantity = 0.00;
  order_status_t status = order_status_t::ORDER_INIT;
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  double timestamp = 0;
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  order_t open_order;
};

struct quote_scoreboard_t {
  quote_t quote;
  double score = 0.00;
  std::string type;
};
} // namespace t
} // namespace Alpaca
#endif
