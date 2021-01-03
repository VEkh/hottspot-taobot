#if !defined ETRADE__STRADDLE_log_prices
#define ETRADE__STRADDLE_log_prices

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float::to_currency
#include "straddle.h"          // ETrade::Straddle, stream_format, symbol
#include <iostream>            // std::cout, std::endl
#include <string>              // std::string

void ETrade::Straddle::log_prices() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.green;
  std::cout << "Buy        (Open)      => Stop Limit: "
            << utils::float_::to_currency(buy_open_order.limit_price)
            << " • Stop: "
            << utils::float_::to_currency(buy_open_order.stop_price)
            << std::endl;

  std::cout << "Buy        (Stop Loss) => Stop Limit: "
            << utils::float_::to_currency(buy_stop_loss_order.limit_price)
            << " • Stop: "
            << utils::float_::to_currency(buy_stop_loss_order.stop_price)
            << std::endl;

  std::cout << "Buy        (Profit)    =>      Limit: "
            << utils::float_::to_currency(buy_profit_order.limit_price)
            << std::endl;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.red;
  std::cout << "Sell Short (Open)      => Stop Limit: "
            << utils::float_::to_currency(sell_short_open_order.limit_price)
            << " • Stop: "
            << utils::float_::to_currency(sell_short_open_order.stop_price)
            << std::endl;

  std::cout << "Sell Short (Stop Loss) => Stop Limit: "
            << utils::float_::to_currency(
                   sell_short_stop_loss_order.limit_price)
            << " • Stop: "
            << utils::float_::to_currency(sell_short_stop_loss_order.stop_price)
            << std::endl;

  std::cout << "Sell Short (Profit)    =>      Limit: "
            << utils::float_::to_currency(sell_short_profit_order.limit_price)
            << std::endl;

  std::cout << fmt.reset;
}

#endif
