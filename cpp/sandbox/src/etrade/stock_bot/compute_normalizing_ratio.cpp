#if !defined ETRADE__STOCK_BOT_compute_normalizing_ratio
#define ETRADE__STOCK_BOT_compute_normalizing_ratio

#include "stock_bot.h" // ETrade::StockBot

double ETrade::StockBot::compute_normalizing_ratio(const double in) {
  const double BASIS = 100.00;
  return BASIS / in;
}

#endif
