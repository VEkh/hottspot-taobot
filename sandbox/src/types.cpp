#ifndef GLOBAL__types
#define GLOBAL__types

#include <map>    // std::map
#include <string> // std::string

namespace Global {
namespace t {
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

struct avg_one_sec_variances_t {
  double latest = 0.00;
  double running = 0.00;
};

enum order_win_result_t {
  LOSS,
  TIE,
  WIN,
};

struct exit_prices_t {
  double stop_loss = 0.00;
  double stop_profit = 0.00;
};

enum order_action_t {
  BUY,
  SELL,
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
  double price = 0.00;
  std::string symbol = "";
  double timestamp;

  double mid() const { return (this->ask + this->bid) / 2.0; };
};

enum trend_t {
  TREND_CONSOLIDATION = 0,
  TREND_DOWN = -1,
  TREND_UP = 1,
};

struct trend_meta_t {
  double at = 0;
  bool is_initialized = false; // TODO: Decide
  trend_t trend = trend_t::TREND_CONSOLIDATION;
};
} // namespace t
} // namespace Global
#endif
