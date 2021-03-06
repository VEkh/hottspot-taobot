#if !defined ETRADE__STOCK_BOT_compute_max_loss
#define ETRADE__STOCK_BOT_compute_max_loss

#include "compute_max_loss.cpp" // compute_max_loss
#include "stock_bot.h"          // ETrade::StockBot,  day_range

double ETrade::StockBot::compute_max_loss() {
  json reference_quote = quotes.front();

  const double MAX_LOSS_PERCENT_PRICE = 0.005;
  const double reference_price = reference_quote["currentPrice"];
  const double y_scale = MAX_LOSS_PERCENT_PRICE;
  const double x = 100 * (day_range / reference_price);
  const double x_shift = -3;

  const double y = y_scale / (1 + exp(-(x + x_shift)));

  return reference_price * y;
}

#endif
