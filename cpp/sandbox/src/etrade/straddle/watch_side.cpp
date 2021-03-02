#if !defined ETRADE__STRADDLE_watch_side
#define ETRADE__STRADDLE_watch_side

/*
 * ETrade::Straddle
 * buy_close_order
 * buy_open_order
 * etrade_client
 * order_status_t
 * order_t
 * position_t
 * sell_short_close_order
 * sell_short_open_order
 * speedometer
 * symbol
 */
#include "straddle.h"

#include "etrade/client/client.h"      // ETrade::Client
#include "lib/formatted.cpp"           // Formatted
#include "set_execution_price.cpp"     // set_execution_price
#include "set_profit.cpp"              // set_profit
#include "set_status.cpp"              // set_status
#include "set_trailing_stop_price.cpp" // set_trailing_stop_price
#include <iostream>                    // std::cout, std::endl
#include <string>                      // std::string

bool should_close(const order_t *close_order, const double current_price) {
  switch (close_order->action) {
  case order_action_t::BUY_TO_COVER: {
    return current_price >= close_order->stop_price;
  }
  case order_action_t::SELL: {
    return current_price <= close_order->stop_price;
  }
  }
}

void ETrade::Straddle::watch_side(const order_action_t &order_action_type) {
  Formatted::fmt_stream_t fmt = stream_format;
  json reference_quote = quotes.front();
  const char *order_action = ETrade::Client::ORDER_ACTIONS[order_action_type];
  const double current_price = quotes.back()["currentPrice"];
  const double day_range = (double)reference_quote["highPrice"] -
                           (double)reference_quote["lowPrice"];

  order_t *close_order;
  std::string log_icon;
  order_t *open_order;
  order_t *opposite_open_order;
  bool should_open;
  bool should_reset_open;

  switch (order_action_type) {
  case order_action_t::BUY: {
    close_order = &buy_close_order;
    log_icon = "📈 ";
    open_order = &buy_open_order;
    opposite_open_order = &sell_short_open_order;

    should_open = current_price >= open_order->stop_price;
    should_reset_open =
        speedometer.displacement <= 0 ||
        (current_price - open_order->stop_price) >= 0.025 * day_range;

    break;
  }
  case order_action_t::SELL_SHORT: {
    close_order = &sell_short_close_order;
    log_icon = "📉 ";
    open_order = &sell_short_open_order;
    opposite_open_order = &buy_open_order;

    should_open = current_price <= open_order->stop_price;
    should_reset_open =
        speedometer.displacement >= 0 ||
        -(current_price - open_order->stop_price) >= 0.025 * day_range;

    break;
  }
  }

  set_status(open_order);
  set_status(close_order);

  if (open_order->status == order_status_t::ORDER_PENDING &&
      opposite_open_order->status == order_status_t::ORDER_PENDING &&
      should_open) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << log_icon << order_action << ": Placing open order."
              << std::endl;
    std::cout << fmt.reset;

    etrade_client.place_order(open_order);

    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << log_icon << order_action << ": Placed open order."
              << std::endl;
    std::cout << fmt.reset;

    return;
  }

  if (open_order->status == order_status_t::ORDER_OPEN && should_reset_open) {
    std::cout << fmt.bold << fmt.cyan << std::endl;
    std::cout << log_icon << order_action << ": Cancelling open order."
              << std::endl;
    std::cout << fmt.reset;

    etrade_client.cancel_order(open_order);

    return;
  }

  if (open_order->status == order_status_t::ORDER_EXECUTED &&
      !open_order->execution_price) {
    std::cout << fmt.bold << fmt.green << std::endl;
    std::cout << log_icon << order_action << ": Executed open order."
              << std::endl;
    std::cout << fmt.reset;

    set_execution_price(open_order);
  }

  if (open_order->status == order_status_t::ORDER_EXECUTED &&
      close_order->status == order_status_t::ORDER_PENDING) {
    set_profit(open_order);
    set_trailing_stop_price(close_order, open_order);

    if (should_close(close_order, current_price)) {
      etrade_client.place_order(close_order);

      std::cout << fmt.bold << fmt.cyan << std::endl;
      std::cout << log_icon << order_action << ": Placed closing order."
                << std::endl;
      std::cout << fmt.reset;

      return;
    }
  }

  if (close_order->status == order_status_t::ORDER_EXECUTED) {
    set_execution_price(close_order);
    set_profit(close_order, open_order);

    if (close_order->profit > 0) {
      std::cout << fmt.bold << fmt.green << std::endl;
      std::cout << "🎉 " << order_action << ": Closed order at a gain."
                << std::endl;
    } else if (close_order->profit == 0) {
      std::cout << fmt.bold << fmt.yellow << std::endl;
      std::cout << "😅 " << order_action << ": Closed order at no loss, no gain."
                << std::endl;
    } else {
      std::cout << fmt.bold << fmt.red << std::endl;
      std::cout << "😭 " << order_action
                << ": Closed order at a loss. Better luck next time!"
                << std::endl;

      next_order_action =
          (char *)ETrade::Client::ORDER_ACTIONS[opposite_open_order->action];
    }

    std::cout << fmt.reset;

    return;
  }
}

#endif
