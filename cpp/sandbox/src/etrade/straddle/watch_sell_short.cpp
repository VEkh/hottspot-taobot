#if !defined ETRADE__STRADDLE_watch_sell_short
#define ETRADE__STRADDLE_watch_sell_short

/*
 * ETrade::Straddle
 * sell_short_open_order
 * sell_short_profit_order
 * order_status_t
 * symbol
 */
#include "straddle.h"

#include "cancel_order.cpp"     // cancel_order
#include "get_order_status.cpp" // get_order_status
#include "lib/formatted.cpp"    // Formatted
#include "order_to_string.cpp"  // order_to_string
#include "place_order.cpp"      // place_order
#include <iostream>             // std::cout, std::endl

void ETrade::Straddle::watch_sell_short() {
  Formatted::fmt_stream_t fmt = stream_format;

  if (sell_short_open_order.id &&
      sell_short_open_order.status == order_status_t::ORDER_OPEN) {
    std::string status = get_order_status(sell_short_open_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      sell_short_open_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "📈 SELL_SHORT: Opened: \n" << std::endl;
      std::cout << order_to_string(sell_short_open_order) << std::endl;
      std::cout << fmt.reset;

      place_order(sell_short_profit_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "SELL_SHORT: Placed the profit order: \n" << std::endl;
      std::cout << order_to_string(sell_short_profit_order) << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }

  if (sell_short_profit_order.id &&
      sell_short_profit_order.status == order_status_t::ORDER_OPEN) {
    std::string status = get_order_status(sell_short_profit_order);
    double current_price = quote["lastPrice"];

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      sell_short_profit_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "🎉 SELL_SHORT: Profit order executed: \n" << std::endl;
      std::cout << order_to_string(sell_short_profit_order) << std::endl;
      std::cout << fmt.reset;

      cancel_order(buy_open_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "SELL_SHORT: Cancelled the SELL_SHORT open order: \n"
                << std::endl;
      std::cout << order_to_string(sell_short_open_order) << std::endl;
      std::cout << fmt.reset;
    } else if (current_price >= sell_short_stop_loss_order.stop_price) {
      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout << "😭 SELL_SHORT: Price passed stop loss threshold. Cancelling "
                   "profit "
                   "order: \n"
                << std::endl;
      std::cout << order_to_string(sell_short_profit_order) << std::endl;
      std::cout << fmt.reset;

      cancel_order(sell_short_profit_order);
      place_order(sell_short_stop_loss_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "SELL_SHORT: Placed the stop loss order: \n" << std::endl;
      std::cout << order_to_string(sell_short_profit_order) << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }

  if (sell_short_stop_loss_order.id &&
      sell_short_stop_loss_order.status == order_status_t::ORDER_OPEN) {
    std::string status = get_order_status(sell_short_stop_loss_order);

    if (status == ORDER_STATUSES[order_status_t::ORDER_EXECUTED]) {
      sell_short_stop_loss_order.status = order_status_t::ORDER_EXECUTED;

      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout << "😭 SELL_SHORT: Stop loss order executed: \n" << std::endl;
      std::cout << order_to_string(sell_short_stop_loss_order) << std::endl;

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << "Better luck next time!" << std::endl;
      std::cout << fmt.reset;
    }

    return;
  }
}

#endif
