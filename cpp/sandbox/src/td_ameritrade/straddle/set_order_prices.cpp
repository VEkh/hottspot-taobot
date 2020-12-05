#if !defined TD_AMERITRADE__STRADDLE_set_order_prices
#define TD_AMERITRADE__STRADDLE_set_order_prices

#include "straddle.h" // TdAmeritrade::Straddle, quote

float TARGET_PROFIT = 0.15;
float TARGET_TOTAL_MOVEMENT = 0.15;

void TdAmeritrade::Straddle::set_order_prices() {
  float current_price = quote["lastPrice"];
  float high = quote["highPrice"];
  float low = quote["lowPrice"];

  float target_profit_ratio = 1 + TARGET_PROFIT;
  float range_movement = TARGET_TOTAL_MOVEMENT / target_profit_ratio;

  float target_movement = ((high - low) * range_movement) / current_price;
  float open_stop_limit_price_change = target_movement * current_price;
  float open_stop_price_change = 0.9 * open_stop_limit_price_change;

  order_prices.buy.open_stop = current_price + open_stop_price_change;
  order_prices.buy.open_stop_limit =
      current_price + open_stop_limit_price_change;
  order_prices.buy.close_limit =
      current_price + (target_profit_ratio * open_stop_limit_price_change);

  order_prices.sell_short.open_stop = current_price - open_stop_price_change;
  order_prices.sell_short.open_stop_limit =
      current_price - open_stop_limit_price_change;
  order_prices.sell_short.close_limit =
      current_price - (target_profit_ratio * open_stop_limit_price_change);
}

#endif
