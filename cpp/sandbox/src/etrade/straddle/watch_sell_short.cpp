#if !defined ETRADE__STRADDLE_watch_sell_short
#define ETRADE__STRADDLE_watch_sell_short

/*
 * ETrade::Straddle
 * sell_short_open_order
 * sell_short_profit_order
 * sell_short_stop_loss_order
 * order_status_t
 * symbol
 */
#include "straddle.h"

#include "adjust_limit_price.cpp"        // adjust_limit_price
#include "cancel_order.cpp"              // cancel_order
#include "lib/formatted.cpp"             // Formatted
#include "place_order.cpp"               // place_order
#include "set_order_execution_price.cpp" // set_order_execution_price
#include "set_order_status.cpp"          // set_order_status
#include <iostream>                      // std::cout, std::endl

void ETrade::Straddle::watch_sell_short() {
  Formatted::fmt_stream_t fmt = stream_format;
  double current_price = quote["lastPrice"];

  set_order_status(sell_short_open_order);
  set_order_status(sell_short_profit_order);
  set_order_status(sell_short_stop_loss_order);

  if (sell_short_open_order.status == order_status_t::ORDER_PENDING &&
      current_price <= sell_short_open_order.stop_price) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "📈 SELL_SHORT: Placing open order." << std::endl;
    std::cout << fmt.reset;

    place_order(sell_short_open_order);

    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << "SELL_SHORT: Placed open order." << std::endl;
    std::cout << fmt.reset;

    return;
  }

  if (sell_short_open_order.status == order_status_t::ORDER_EXECUTED &&
      sell_short_profit_order.status == order_status_t::ORDER_PENDING) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "📉 SELL_SHORT: Executed open order." << std::endl;
    std::cout << fmt.reset;

    set_order_execution_price(sell_short_open_order);
    adjust_limit_price(sell_short_profit_order, sell_short_open_order);
    place_order(sell_short_profit_order);

    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << "SELL_SHORT: Placed the profit order." << std::endl;
    std::cout << fmt.reset;

    return;
  }

  if (sell_short_profit_order.status == order_status_t::ORDER_EXECUTED) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "🎉 SELL_SHORT: Executed profit order." << std::endl;
    std::cout << fmt.reset;

    if (buy_open_order.status == order_status_t::ORDER_OPEN) {
      cancel_order(buy_open_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "SELL_SHORT: Cancelled the BUY open order." << std::endl;
      std::cout << fmt.reset;

      return;
    }
  }

  if (sell_short_profit_order.status == order_status_t::ORDER_OPEN &&
      current_price >= sell_short_stop_loss_order.stop_price) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout
        << "😱 SELL_SHORT: Price passed stop loss threshold. Cancelling profit "
           "order."
        << std::endl;
    std::cout << fmt.reset;

    cancel_order(sell_short_profit_order);

    return;
  }

  if (sell_short_profit_order.status == order_status_t::ORDER_CANCELLED &&
      sell_short_stop_loss_order.status == order_status_t::ORDER_PENDING) {
    place_order(sell_short_stop_loss_order);

    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << "SELL_SHORT: Placed the stop loss order." << std::endl;
    std::cout << fmt.reset;

    return;
  }

  if (sell_short_stop_loss_order.status == order_status_t::ORDER_EXECUTED) {
    std::cout << fmt.bold << fmt.red << std::endl;
    std::cout
        << "😭 SELL_SHORT: Executed stop loss order. Better luck next time!"
        << std::endl;
    std::cout << fmt.reset;
  }
}

#endif
