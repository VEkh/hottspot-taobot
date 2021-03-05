#if !defined ETRADE__STRADDLE_set_order_prices
#define ETRADE__STRADDLE_set_order_prices

/*
 * ENTRY_DAY_RANGE_RATIO
 * ETrade::Straddle
 * buy_open_order
 * buy_close_order
 * init_order_action
 * quotes
 * sell_short_open_order
 * sell_short_close_order
 */
#include "straddle.h"

#include "etrade/deps.cpp"     // json
#include "lib/utils/float.cpp" // utils::float_
#include <algorithm>           // std::max, std::min
#include <math.h>              // INFINITY
#include <string>              // string

void ETrade::Straddle::set_order_prices() {
  const json first_quote = quotes.front();
  const double reference_price = first_quote["currentPrice"];

  day_range =
      (double)first_quote["highPrice"] - (double)first_quote["lowPrice"];

  const double entry_delta = day_range * ENTRY_DAY_RANGE_RATIO;
  const double entry_limit_delta = entry_delta;
  const double entry_stop_delta = 0.8 * entry_limit_delta;

  buy_open_order.action = order_action_t::BUY;
  buy_open_order.limit_price =
      utils::float_::to_currency(reference_price + entry_limit_delta);
  buy_open_order.quantity = quantity;
  buy_open_order.stop_price =
      utils::float_::to_currency(reference_price + entry_stop_delta);
  buy_open_order.symbol = symbol;
  buy_open_order.type = order_type_t::MARKET;

  buy_close_order.action = order_action_t::SELL;
  buy_close_order.quantity = quantity;
  buy_close_order.stop_price = -INFINITY;
  buy_close_order.symbol = symbol;
  buy_close_order.type = order_type_t::MARKET;

  sell_short_open_order.action = order_action_t::SELL_SHORT;
  sell_short_open_order.limit_price =
      utils::float_::to_currency(reference_price - entry_limit_delta);
  sell_short_open_order.quantity = quantity;
  sell_short_open_order.stop_price =
      utils::float_::to_currency(reference_price - entry_stop_delta);
  sell_short_open_order.symbol = symbol;
  sell_short_open_order.type = order_type_t::MARKET;

  sell_short_close_order.action = order_action_t::BUY_TO_COVER;
  sell_short_close_order.quantity = quantity;
  sell_short_close_order.stop_price = INFINITY;
  sell_short_close_order.symbol = symbol;
  sell_short_close_order.type = order_type_t::MARKET;

  if (init_order_action != nullptr) {
    order_action_t init_order_action_t =
        ETrade::Client::to_order_action_t(init_order_action);

    if (init_order_action_t == order_action_t::BUY) {
      buy_open_order.stop_price = -INFINITY;
    } else if (init_order_action_t == order_action_t::SELL_SHORT) {
      sell_short_open_order.stop_price = INFINITY;
    }
  }
}

#endif
