#if !defined ETRADE__STRADDLE_watch_sell_short
#define ETRADE__STRADDLE_watch_sell_short

/*
 * ETrade::Straddle
 * etrade_client
 * sell_short_open_order
 * sell_short_close_order
 * sell_short_stop_loss_order
 * order_status_t
 * symbol
 */
#include "straddle.h"

#include "fetch_and_set_orders.cpp"    // fetch_and_set_orders
#include "lib/formatted.cpp"           // Formatted
#include "set_execution_price.cpp"     // set_execution_price
#include "set_profit.cpp"              // set_profit
#include "set_status.cpp"              // set_status
#include "set_trailing_stop_price.cpp" // set_trailing_stop_price
#include <iostream>                    // std::cout, std::endl

void ETrade::Straddle::watch_sell_short() {
  Formatted::fmt_stream_t fmt = stream_format;
  double current_price = quotes.back()["currentPrice"];

  set_status(sell_short_open_order);
  set_status(sell_short_close_order);

  if (sell_short_open_order.status == order_status_t::ORDER_PENDING &&
      buy_open_order.status == order_status_t::ORDER_PENDING &&
      current_price <= sell_short_open_order.stop_price) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << "📉 SELL_SHORT: Placing open order." << std::endl;
    std::cout << fmt.reset;

    etrade_client.place_order(sell_short_open_order);

    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << "📉 SELL_SHORT: Placed open order." << std::endl;
    std::cout << fmt.reset;

    return;
  }

  if (sell_short_open_order.status == order_status_t::ORDER_EXECUTED) {
    if (!sell_short_open_order.execution_price) {
      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "📉 SELL_SHORT: Executed open order." << std::endl;
      std::cout << fmt.reset;

      set_execution_price(sell_short_open_order);
    }

    if (sell_short_close_order.status != order_status_t::ORDER_EXECUTED) {
      set_profit(sell_short_open_order);
    }
  }

  if (sell_short_open_order.status == order_status_t::ORDER_EXECUTED &&
      sell_short_close_order.status == order_status_t::ORDER_PENDING) {
    set_trailing_stop_price(sell_short_close_order, sell_short_open_order);

    if (current_price > sell_short_close_order.stop_price) {
      etrade_client.place_order(sell_short_close_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "📉 SELL_SHORT: Placed closing order." << std::endl;
      std::cout << fmt.reset;

      return;
    }
  }

  if (sell_short_close_order.status == order_status_t::ORDER_EXECUTED) {
    set_execution_price(sell_short_close_order);
    set_profit(sell_short_close_order, sell_short_open_order);

    if (sell_short_close_order.execution_price <
        sell_short_open_order.execution_price) {
      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "🎉 SELL_SHORT: Closed order at a gain." << std::endl;
    } else if (sell_short_close_order.execution_price ==
               sell_short_open_order.execution_price) {
      std::cout << fmt.bold << fmt.yellow << std::endl;
      std::cout << "😅 SELL_SHORT: Closed order at no loss, no gain."
                << std::endl;
    } else {
      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout
          << "😭 SELL_SHORT: Closed order at a loss. Better luck next time!"
          << std::endl;

      if (buy_open_order.status == order_status_t::ORDER_PENDING) {
        etrade_client.place_order(buy_open_order);
        buy_open_order.status = order_status_t::ORDER_OPEN;

        std::cout << fmt.bold << fmt.cyan << std::endl;
        std::cout << "📈 BUY: Placed open order." << std::endl;
        std::cout << fmt.reset;

        fetch_and_set_orders();
      };
    }

    std::cout << fmt.reset;

    return;
  }
}

#endif
