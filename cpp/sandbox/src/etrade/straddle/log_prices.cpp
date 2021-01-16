#if !defined ETRADE__STRADDLE_log_prices
#define ETRADE__STRADDLE_log_prices

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float::to_currency
#include "straddle.h"          // ETrade::Straddle, stream_format, symbol
#include <iomanip>             // std::setprecision
#include <iostream>            // std::cout, std::endl, std::fixed
#include <string>              // std::string

void ETrade::Straddle::log_prices() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << std::setprecision(2) << std::fixed;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.green;
  std::cout << "BUY" << std::endl;
  std::cout << "---" << std::endl;
  std::cout << "Open      => Stop: "
            << utils::float_::to_currency(buy_open_order.limit_price)
            << " • Limit: "
            << utils::float_::to_currency(buy_open_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_open_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_open_order.profit) << std::endl;

  std::cout << "Stop Loss => Stop: "
            << utils::float_::to_currency(buy_stop_loss_order.limit_price)
            << " • Limit: "
            << utils::float_::to_currency(buy_stop_loss_order.stop_price)
            << std::endl;

  std::cout << "Profit    => Stop: "
            << utils::float_::to_currency(buy_profit_order.stop_price)
            << " • Limit: "
            << utils::float_::to_currency(buy_profit_order.limit_price)
            << " • Execution: "
            << utils::float_::to_currency(buy_profit_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(buy_profit_order.profit) << std::endl;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.red;
  std::cout << "SELL SHORT" << std::endl;
  std::cout << "----------" << std::endl;
  std::cout << "Open      => Stop: "
            << utils::float_::to_currency(sell_short_open_order.limit_price)
            << " • Limit: "
            << utils::float_::to_currency(sell_short_open_order.stop_price)
            << " • Execution: "
            << utils::float_::to_currency(sell_short_open_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(sell_short_open_order.profit)
            << std::endl;

  std::cout << "Stop Loss => Stop: "
            << utils::float_::to_currency(
                   sell_short_stop_loss_order.limit_price)
            << " • Limit: "
            << utils::float_::to_currency(sell_short_stop_loss_order.stop_price)
            << std::endl;

  std::cout << "Profit    => Stop: "
            << utils::float_::to_currency(sell_short_profit_order.stop_price)
            << " • Limit: "
            << utils::float_::to_currency(sell_short_profit_order.limit_price)
            << " • Execution: "
            << utils::float_::to_currency(
                   sell_short_profit_order.execution_price)
            << " • Profit: "
            << utils::float_::to_currency(sell_short_profit_order.profit)
            << std::endl;

  std::cout << fmt.reset;
}

#endif
