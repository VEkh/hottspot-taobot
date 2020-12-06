#if !defined TD_AMERITRADE__STRADDLE_log_manual_run_prices
#define TD_AMERITRADE__STRADDLE_log_manual_run_prices

#include "lib/formatted.cpp"   // Formatted
#include "lib/utils/float.cpp" // utils::float::toCurrency
#include "straddle.h"          // TdAmeritrade::Straddle, stream_format, symbol
#include <iostream>            // std::cout, std::endl
#include <string>              // std::string

void TdAmeritrade::Straddle::log_manual_run_prices() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::cout << std::endl
            << fmt.bold << fmt.blue << symbol << fmt.cyan
            << "'s Manual Straddle Prices:" << fmt.reset << std::endl;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.green;
  std::cout << "Buy (Open)         => Stop Limit: "
            << utils::float_::toCurrency(order_prices.buy.open_stop_limit)
            << " • Stop: "
            << utils::float_::toCurrency(order_prices.buy.open_stop)
            << std::endl;

  std::cout << "Buy (Close)        =>      Limit: "
            << utils::float_::toCurrency(order_prices.buy.close_limit)
            << std::endl;

  std::cout << std::endl;
  std::cout << fmt.bold << fmt.red;
  std::cout << "Sell Short (Open)  => Stop Limit: "
            << utils::float_::toCurrency(
                   order_prices.sell_short.open_stop_limit)
            << " • Stop: "
            << utils::float_::toCurrency(order_prices.sell_short.open_stop)
            << std::endl;

  std::cout << "Sell Short (Close) =>      Limit: "
            << utils::float_::toCurrency(order_prices.sell_short.close_limit)
            << std::endl;

  std::cout << fmt.reset;
}

#endif
