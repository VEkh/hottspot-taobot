#if !defined ETRADE__STOCK_BOT_compute_door_delta
#define ETRADE__STOCK_BOT_compute_door_delta

#include "stock_bot.h" // ETrade::StockBot,  day_range, quotes

double ETrade::StockBot::compute_door_delta() {
  json reference_quote = quotes.front();

  const double reference_price = reference_quote["currentPrice"];
  const double x = day_range / reference_price;
  const double x_scale = 100.0;
  const double y_scale = 200.0;
  const double y_shift = 3;

  const double y = (y_scale / (1 + exp(x_scale * x))) + y_shift;

  return y * day_range;
}

#endif
