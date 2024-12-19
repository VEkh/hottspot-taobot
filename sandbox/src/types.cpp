#ifndef GLOBAL__types
#define GLOBAL__types

#include <map>    // std::map
#include <math.h> // INFINITY, abs
#include <string> // std::string

namespace Global {
namespace t {
enum order_action_t {
  BUY,
  SELL,
};

enum order_type_t {
  LIMIT,
  MARKET,
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

enum reversal_type_t {
  REVERSAL_HIGH,
  REVERSAL_LOW,
  REVERSAL_NULL,
};

enum stop_profit_type_t {
  STOP_PROFIT_CROSS_RANGE,
  STOP_PROFIT_EXTEND_RANGE,
  STOP_PROFIT_NULL,
};

enum trend_t {
  TREND_CONSOLIDATION = 0,
  TREND_DOWN = -1,
  TREND_UP = 1,
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

struct candle_t {
  double close = 0.0;
  double closed_at = 0.0;
  double high = -INFINITY;
  double high_at = 0.0;
  double low = INFINITY;
  double low_at = 0.0;
  double open = 0.0;
  double opened_at = 0.0;
  std::string symbol;

  double duration_seconds() { return this->closed_at - this->opened_at; };

  double range() { return this->high - this->low; };

  double range_open_percent() { return 100.0 * this->range() / this->open; };

  trend_t trend() {
    if (this->close > this->open) {
      return trend_t::TREND_UP;
    }

    if (this->close < this->open) {
      return trend_t::TREND_DOWN;
    }

    return trend_t::TREND_CONSOLIDATION;
  };
};

struct exit_prices_t {
  double stop_loss = 0.00;
  double stop_profit = 0.00;
};

struct market_epochs_t {
  double close = 0.0;
  double open = 0.0;
  double pre = 0.0;
};

struct order_win_result_streak_t {
  std::map<int, int> counts;
  int current = 0;
  int longest = 0;
};

struct performance_t {
  double current_balance = 0.00;
  double current_loss_streak_balance = 0.00;
  order_win_result_streak_t loss_streaks;
  double max_balance = 0.00;
  std::map<order_win_result_t, int> results;
  std::string symbol;
  order_win_result_streak_t win_streaks;
};

struct quote_t {
  double ask = 0.00;
  double bid = 0.00;
  long int id = 0;
  std::string symbol = "";
  double timestamp;

  bool empty() const { return !this->ask && !this->bid; };
  double mid() const { return (this->ask + this->bid) / 2.0; };
  double spread() const { return this->ask - this->bid; };
};

struct reversal_t {
  double at = 0;
  bool is_record = false;
  bool is_record_only_reversible = true; // TODO: Decide
  bool is_reversible = false;            // TODO: Decide
  bool is_running_record = false;
  double mid = 0;
  int timeframe_minutes = 0;
  reversal_type_t type = reversal_type_t::REVERSAL_NULL;

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
  int timeframe_seconds() { return this->timeframe_minutes * 60; }
};

struct trend_meta_t {
  double at = 0;
  bool is_initialized = false; // TODO: Decide
  trend_t trend = trend_t::TREND_CONSOLIDATION;
};
} // namespace t
} // namespace Global
#endif
