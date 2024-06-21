#ifndef ALPACA__types
#define ALPACA__types

#include "src/types.cpp" // Global::t
#include <math.h>        // INFINITY
#include <string>        // std::string

namespace Alpaca {
namespace t {
using order_action_t = Global::t::order_action_t;
using order_win_result_t = Global::t::order_win_result_t;
using quote_t = Global::t::quote_t;
using trend_meta_t = Global::t::trend_meta_t;
using trend_t = Global::t::trend_t;

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
  ORDER_REJECTED,
  ORDER_REPLACED,
};

enum order_time_in_force_t {
  DAY,
};

enum order_type_t {
  LIMIT,
  MARKET,
};

enum reversal_type_t {
  REVERSAL_HIGH,
  REVERSAL_LOW,
  REVERSAL_NULL,
};

struct reversal_t {
  double at = 0;
  bool is_record = false;
  bool is_running_record = false;
  double mid = 0;
  int timeframe_minutes = 0;
  reversal_type_t type;

  reversal_type_t opposite_type() {
    switch (this->type) {
    case reversal_type_t::REVERSAL_HIGH: {
      return reversal_type_t::REVERSAL_LOW;
    }
    case reversal_type_t::REVERSAL_LOW: {
      return reversal_type_t::REVERSAL_HIGH;
    }
    default: {
      return reversal_type_t::REVERSAL_NULL;
    }
    }
  }

  trend_t to_trend_type() {
    switch (this->type) {
    case reversal_type_t::REVERSAL_HIGH: {
      return trend_t::TREND_DOWN;
    }
    case reversal_type_t::REVERSAL_LOW: {
      return trend_t::TREND_UP;
    }
    default: {
      return trend_t::TREND_CONSOLIDATION;
    }
    }
  }
};

struct reversals_t {
  int candles_count = 0;
  std::map<double, reversal_t> highs;
  std::map<double, reversal_t> lows;
  std::map<std::string, int> record_counts;
  int timeframe_minutes = 0;

  bool any_empty() { return this->highs.empty() || this->lows.empty(); }
  bool every_empty() { return this->highs.empty() && this->lows.empty(); }
};

struct order_t {
  order_action_t action = order_action_t::BUY;
  double day_range = 0.00; // TODO: Decide
  reversal_t entry_reversal;
  double execution_price = 0.00;
  std::string id = "";
  double limit_price = 0.00;
  double max_position_profit = 0.00;
  double max_profit = 0.00;
  double max_profit_at = 0;
  double min_profit = 0.00;
  double min_profit_at = 0;
  double profit = 0.00;
  double quantity = 0.00;
  order_status_t status = order_status_t::ORDER_INIT;
  double stop_loss = 0.00;
  double stop_profit = 0.00;
  reversal_t stop_profit_reversal; // TODO: Decide
  std::string symbol;
  order_time_in_force_t time_in_force = order_time_in_force_t::DAY;
  double timestamp = 0;
  trend_meta_t trend; // TODO: Decide
  order_type_t type = order_type_t::MARKET;
};

struct position_t {
  order_t close_order;
  order_t open_order;
};
} // namespace t
} // namespace Alpaca
#endif
