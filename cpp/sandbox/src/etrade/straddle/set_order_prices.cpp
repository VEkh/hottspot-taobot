#if !defined ETRADE__STRADDLE_set_order_prices
#define ETRADE__STRADDLE_set_order_prices

#include "straddle.h" // ETrade::Straddle, quote

float TARGET_PROFIT = 0.15;
float TARGET_TOTAL_MOVEMENT = 0.10;

void ETrade::Straddle::set_order_prices() {
  float current_price = quote["lastPrice"];
  float high = quote["highPrice"];
  float low = quote["lowPrice"];

  float target_profit_ratio = 1 + TARGET_PROFIT;
  float range_movement = TARGET_TOTAL_MOVEMENT / target_profit_ratio;

  float target_movement = ((high - low) * range_movement) / current_price;
  float open_stop_limit_price_change = target_movement * current_price;
  float open_stop_price_change = 0.9 * open_stop_limit_price_change;

  buy_open_order.action = order_action_t::BUY;
  buy_open_order.limit_price = current_price + open_stop_limit_price_change;
  buy_open_order.stop_price = current_price + open_stop_price_change;
  buy_open_order.type = order_type_t::STOP_LIMIT;

  buy_profit_order.action = order_action_t::SELL;
  buy_profit_order.limit_price =
      current_price + (target_profit_ratio * open_stop_limit_price_change);
  buy_profit_order.type = order_type_t::LIMIT;

  buy_stop_loss_order.action = order_action_t::SELL;
  buy_stop_loss_order.limit_price =
      current_price -
      (1.01 * target_profit_ratio * open_stop_limit_price_change);
  buy_stop_loss_order.stop_price =
      current_price - (target_profit_ratio * open_stop_limit_price_change);
  buy_stop_loss_order.type = order_type_t::STOP_LIMIT;

  sell_short_open_order.action = order_action_t::SELL_SHORT;
  sell_short_open_order.limit_price =
      current_price - open_stop_limit_price_change;
  sell_short_open_order.stop_price = current_price - open_stop_price_change;
  sell_short_open_order.type = order_type_t::STOP_LIMIT;

  sell_short_profit_order.action = order_action_t::BUY_TO_COVER;
  sell_short_profit_order.limit_price =
      current_price - (target_profit_ratio * open_stop_limit_price_change);
  sell_short_profit_order.type = order_type_t::LIMIT;

  sell_short_stop_loss_order.action = order_action_t::BUY_TO_COVER;
  sell_short_stop_loss_order.limit_price =
      current_price +
      (1.01 * target_profit_ratio * open_stop_limit_price_change);
  sell_short_stop_loss_order.stop_price =
      current_price + (target_profit_ratio * open_stop_limit_price_change);
  sell_short_stop_loss_order.type = order_type_t::STOP_LIMIT;
}

#endif
