#if !defined ETRADE__STRADDLE_set_order_prices
#define ETRADE__STRADDLE_set_order_prices

/*
 * ETrade::Straddle
 * buy_open_order
 * buy_close_order
 * quotes
 * sell_short_open_order
 * sell_short_close_order
 */
#include "straddle.h"

#include "etrade/deps.cpp"     // json
#include "lib/utils/float.cpp" // utils::float_
#include <math.h>              // INFINITY

double ENTRY_THRESHOLD = 0.0015;

void ETrade::Straddle::set_order_prices() {
  json first_quote = quotes.front();

  double reference_price = first_quote["currentPrice"];

  double entry_delta = reference_price * ENTRY_THRESHOLD;

  buy_open_order.action = order_action_t::BUY;
  buy_open_order.quantity = quantity;
  buy_open_order.stop_price =
      utils::float_::to_currency(reference_price + entry_delta);
  buy_open_order.symbol = symbol;
  buy_open_order.type = order_type_t::MARKET;

  buy_close_order.action = order_action_t::SELL;
  buy_close_order.quantity = quantity;
  buy_close_order.stop_price = -INFINITY;
  buy_close_order.symbol = symbol;
  buy_close_order.type = order_type_t::MARKET;

  sell_short_open_order.action = order_action_t::SELL_SHORT;
  sell_short_open_order.quantity = quantity;
  sell_short_open_order.stop_price =
      utils::float_::to_currency(reference_price - entry_delta);
  sell_short_open_order.symbol = symbol;
  sell_short_open_order.type = order_type_t::MARKET;

  sell_short_close_order.action = order_action_t::BUY_TO_COVER;
  sell_short_close_order.quantity = quantity;
  sell_short_close_order.stop_price = INFINITY;
  sell_short_close_order.symbol = symbol;
  sell_short_close_order.type = order_type_t::MARKET;
}

#endif
