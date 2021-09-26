#ifndef OANDA__TAO_BOT_H
#define OANDA__TAO_BOT_H

#include "lib/formatted.cpp"       // Formatted
#include "oanda/client/client.cpp" // Oanda::Client
#include "oanda/types.cpp"         // Oanda::t
#include "types.cpp"               // Global::t
#include <list>                    // std::list
#include <map>                     // std::map
#include <string>                  // std::string
#include <vector>                  // std::map

namespace Oanda {
class TaoBot {
public:
  TaoBot(char *, std::map<std::string, std::string> &);

  void run();

private:
  using account_balance_t = Global::t::account_balance_t;
  using candlestick_t = Global::t::candlestick_t;
  using closed_positions_stats_t = Global::t::closed_positions_stats_t;
  using exit_prices_t = Global::t::exit_prices_t;
  using order_status_t = Oanda::t::order_status_t;
  using order_t = Oanda::t::order_t;
  using order_win_result_streak_t = Global::t::order_win_result_streak_t;
  using order_win_result_t = Global::t::order_win_result_t;
  using position_t = Oanda::t::position_t;
  using quote_t = Global::t::quote_t;

  const double AVERAGE_TICK_PRICE_DELTA_PERIOD = 3.0 * 60.0;
  const double POLLING_INTERVAL_SECONDS = 1.0;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  Oanda::Client api_client;
  account_balance_t account_balance;
  account_balance_t original_account_balance;
  bool is_long_position;
  char *symbol;
  double average_tick_price_delta = 0.00;
  double long_average_buy_sell_ratio;
  double long_average_sell_buy_ratio;
  double short_average_buy_sell_ratio;
  double short_average_sell_buy_ratio;
  exit_prices_t exit_prices;
  int quantity;
  order_t *close_order_ptr = nullptr;
  order_t *open_order_ptr = nullptr;
  order_t close_order;
  order_t open_order;
  std::list<candlestick_t> candlesticks;
  std::vector<position_t> closed_positions;
  std::vector<quote_t> quotes;

  account_balance_t fetch_account_balance();

  bool is_end_of_trading_period();
  bool is_market_open();
  bool should_terminate();

  double profit_percentage(const order_t *);

  closed_positions_stats_t build_closed_positions_stats();
  order_win_result_t order_win_result(const order_t *);

  std::map<int, std::map<const char *, double>>
  build_moving_buy_sell_ratio_average(std::vector<int> &);

  void await_market_open();
  void build_candlesticks();
  void initialize(char *, std::map<std::string, std::string> &);
  void fetch_quote();
  void log_account_balance();
  void log_average_tick_price_delta();
  void log_candlesticks();
  void log_closed_positions();
  void log_position();
  void log_quote();
  void log_start_message();
  void set_and_log_buy_sell_ratios();
  void set_average_tick_price_delta();
  void watch();
};
} // namespace Oanda

#endif
