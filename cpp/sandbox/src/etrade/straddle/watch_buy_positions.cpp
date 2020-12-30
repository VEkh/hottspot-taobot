#if !defined ETRADE__STRADDLE_watch_buy_positions
#define ETRADE__STRADDLE_watch_buy_positions

/*
 * ETrade::Straddle
 * buy_open_order
 * buy_profit_order
 * order_status_t
 * symbol
 */
#include "straddle.h"

#include "get_order_status.cpp" // get_order_status
#include "lib/formatted.cpp"    // Formatted
#include "order_to_string.cpp"  // order_to_string
#include "place_order.cpp"      // place_order
#include <iostream>             // std::cout, std::endl

void ETrade::Straddle::watch_buy_positions() {
  Formatted::fmt_stream_t fmt = stream_format;

  if (buy_open_order.id &&
      buy_open_order.status == order_status_t::ORDER_OPEN) {
    const char *status = get_order_status(buy_open_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      buy_open_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;

      std::cout << "📈 Buy open order executed: \n" << std::endl;
      std::cout << order_to_string(buy_open_order) << std::endl;

      place_order(buy_profit_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "Opened the profit order: \n" << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }

  if (buy_profit_order.id &&
      buy_profit_order.status == order_status_t::ORDER_OPEN) {
    const char *status = get_order_status(buy_profit_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      buy_profit_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;

      std::cout << "🎉 Buy profit order executed: \n" << std::endl;
      std::cout << order_to_string(buy_profit_order) << std::endl;

      etrade_client.cancel_order(sell_short_open_order.id);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "Cancelled the SELL_SHORT open order: \n" << std::endl;
      std::cout << order_to_string(sell_short_open_order) << std::endl;
      std::cout << fmt.reset;

      exit(0);
    }

    return;
  }
}

#endif
