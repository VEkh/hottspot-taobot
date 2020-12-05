#if !defined TD_AMERITRADE__STRADDLE_manual_run
#define TD_AMERITRADE__STRADDLE_manual_run

#include "fetch_current_quote.cpp" // fetch_current_quote
#include "set_order_prices.cpp"    // set_order_prices
#include "straddle.h" // TdAmeritrade::Straddle, stream_format, symbol, td_ameritrade_client
#include "utils/float.cpp" // utils::float::toCurrency
#include <iostream>        // std::cout, std::endl
#include <string>          // std::string

void log_symbol(std::string symbol) {
  std::cout << std::endl << symbol << std::endl;

  for (int i = 0; i < symbol.size(); i++) {
    std::cout << "-";
  }

  std::cout << std::endl;
}

void TdAmeritrade::Straddle::manual_run() {
  td_ameritrade_client.refresh_tokens();
  fetch_current_quote();
  set_order_prices();
  log_symbol(symbol);

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "BUY (OPEN)                  => Stop Limit: "
            << utils::float_::toCurrency(order_prices.buy.open_stop_limit)
            << " • Stop: "
            << utils::float_::toCurrency(order_prices.buy.open_stop)
            << std::endl;

  std::cout << "BUY (CLOSE) (PROFIT)        =>      Limit: "
            << utils::float_::toCurrency(order_prices.buy.close_limit)
            << std::endl;

  std::cout << "\n=========================\n" << std::endl;

  std::cout << "SELL SHORT (OPEN)           => Stop Limit: "
            << utils::float_::toCurrency(
                   order_prices.sell_short.open_stop_limit)
            << " • Stop: "
            << utils::float_::toCurrency(order_prices.sell_short.open_stop)
            << std::endl;

  std::cout << "SELL SHORT (CLOSE) (PROFIT) =>      Limit: "
            << utils::float_::toCurrency(order_prices.sell_short.close_limit)
            << std::endl;
}

#endif
