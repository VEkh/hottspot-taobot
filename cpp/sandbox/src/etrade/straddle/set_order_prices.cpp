#if !defined ETRADE__STRADDLE_set_order_prices
#define ETRADE__STRADDLE_set_order_prices

/*
 * ETrade::Straddle
 * buy_open_order
 * buy_profit_order
 * buy_stop_loss_order
 * quote
 * sell_short_open_order
 * sell_short_profit_order
 * sell_short_stop_loss_order
 */
#include "straddle.h"

#include "lib/utils/float.cpp" // utils::float_

double MINIMUM_CURRENT_PRICE_DELTA = 0.005;
double TARGET_PROFIT = 0.05;
double TARGET_TOTAL_MOVEMENT = 0.05;

void ETrade::Straddle::set_order_prices() {
  double current_price = quote["lastPrice"];

  double default_high = current_price * (1 + MINIMUM_CURRENT_PRICE_DELTA);
  double default_low = current_price * (1 - MINIMUM_CURRENT_PRICE_DELTA);

  double high =
      (double)quote["highPrice"] ? (double)quote["highPrice"] : default_high;

  double low =
      (double)quote["lowPrice"] ? (double)quote["lowPrice"] : default_low;

  double target_movement = (high - low) * TARGET_TOTAL_MOVEMENT;
  double open_stop_limit_price_change = (1 - TARGET_PROFIT) * target_movement;
  double open_stop_price_change = 0.8 * open_stop_limit_price_change;

  buy_open_order.action = order_action_t::BUY;
  buy_open_order.limit_price =
      utils::float_::to_currency(current_price + open_stop_limit_price_change);
  buy_open_order.stop_price =
      utils::float_::to_currency(current_price + open_stop_price_change);
  buy_open_order.type = order_type_t::MARKET;

  buy_profit_order.action = order_action_t::SELL;
  buy_profit_order.limit_price =
      utils::float_::to_currency(current_price + target_movement);
  buy_profit_order.type = order_type_t::LIMIT;

  sell_short_open_order.action = order_action_t::SELL_SHORT;
  sell_short_open_order.limit_price =
      utils::float_::to_currency(current_price - open_stop_limit_price_change);
  sell_short_open_order.stop_price =
      utils::float_::to_currency(current_price - open_stop_price_change);
  sell_short_open_order.type = order_type_t::MARKET;

  sell_short_profit_order.action = order_action_t::BUY_TO_COVER;
  sell_short_profit_order.limit_price =
      utils::float_::to_currency(current_price - target_movement);
  sell_short_profit_order.type = order_type_t::LIMIT;

  buy_stop_loss_order.action = order_action_t::SELL;
  buy_stop_loss_order.limit_price = sell_short_open_order.limit_price;
  buy_stop_loss_order.stop_price = sell_short_open_order.stop_price;
  buy_stop_loss_order.type = order_type_t::MARKET;

  sell_short_stop_loss_order.action = order_action_t::BUY_TO_COVER;
  sell_short_stop_loss_order.limit_price = buy_open_order.limit_price;
  sell_short_stop_loss_order.stop_price = buy_open_order.stop_price;
  sell_short_stop_loss_order.type = order_type_t::MARKET;
}

#endif
