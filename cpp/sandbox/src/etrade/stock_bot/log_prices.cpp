#if !defined ETRADE__STOCK_BOT_log_prices
#define ETRADE__STOCK_BOT_log_prices

/*
 * ETrade::StockBot
 * buy_open_order
 * buy_close_order
 * sell_short_open_order
 * sell_short_close_order
 * stream_format
 * symbol
 */
#include "stock_bot.h"

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float::to_currency
#include <iomanip>             // std::setprecision
#include <iostream>            // std::cout, std::endl, std::fixed
#include <string>              // std::string
#include <vector>              // std::vector

void ETrade::StockBot::log_prices() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::vector<std::string> buy_statuses = {
      std::string("Open: ") +
          ETrade::Client::ORDER_STATUSES[buy_open_order.status],
      std::string("Close: ") +
          ETrade::Client::ORDER_STATUSES[buy_close_order.status],
  };

  std::vector<std::string> sell_short_statuses = {
      std::string("Open: ") +
          ETrade::Client::ORDER_STATUSES[sell_short_open_order.status],
      std::string("Close: ") +
          ETrade::Client::ORDER_STATUSES[sell_short_close_order.status],
  };

  std::cout << std::setprecision(2) << std::fixed;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.green;
  std::cout << "BUY" << std::endl;
  std::cout << "---" << std::endl;
  std::cout << "Open        => Stop: "
            << utils::float_::to_currency(buy_open_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_open_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_open_order.profit) << std::endl;

  std::cout << "Open (SMA)  => Stop: "
            << utils::float_::to_currency(buy_open_order.sma_stop_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_open_order.sma_execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_open_order.sma_profit)
            << std::endl;

  std::cout << "Close       => Stop: "
            << utils::float_::to_currency(buy_close_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_close_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_close_order.profit) << std::endl;

  std::cout << "Close (SMA) => Stop: "
            << utils::float_::to_currency(buy_close_order.sma_stop_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_close_order.sma_execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_close_order.sma_profit)
            << std::endl;

  std::cout << "Status    => " << utils::vector::join(buy_statuses, " • ")
            << std::endl;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.red;
  std::cout << "SELL SHORT" << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << "Open       => Stop: "
            << utils::float_::to_currency(sell_short_open_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(sell_short_open_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(sell_short_open_order.profit)
            << std::endl;

  std::cout << "Close      => Stop: "
            << utils::float_::to_currency(sell_short_close_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(
                   sell_short_close_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(sell_short_close_order.profit)
            << std::endl;

  std::cout << "Status    => "
            << utils::vector::join(sell_short_statuses, " • ") << std::endl;

  std::cout << fmt.reset;
}

#endif
