#ifndef GLOBAL__types
#define GLOBAL__types

namespace Global {
namespace t {
struct account_balance_t {
  double balance;
  double margin_buying_power;
};

struct candlestick_t {
  std::string clock_time;
  double close;
  double high;
  double low;
  double open;
};

struct exit_prices_t {
  double max_loss = 0.00;
  double min_profit = 0.00;
  double secure_profit_lower = 0.00;
  double secure_profit_upper = 0.00;
};

struct quote_t {
  double price;
  long int timestamp;
};
} // namespace t
} // namespace Global
#endif
