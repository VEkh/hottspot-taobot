#if !defined ETRADE__STRADDLE_log_order_statuses
#define ETRADE__STRADDLE_log_order_statuses

#include "lib/formatted.cpp"    // Formatted
#include "lib/utils/string.cpp" // utils::string
#include "straddle.h"           // ETrade::Straddle, stream_format, symbol
#include <iostream>             // std::cout, std::endl
#include <string>               // std::string
#include <vector>               // std::vector

void ETrade::Straddle::log_order_statuses() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::vector<std::string> buy_statuses = {
      std::string("BUY                    |  Open: ") +
          ORDER_STATUSES[buy_open_order.status],
      std::string("Profit: ") + ORDER_STATUSES[buy_profit_order.status],
      std::string("Stop Loss: ") + ORDER_STATUSES[buy_stop_loss_order.status],
  };

  std::vector<std::string> sell_short_statuses = {
      std::string("SELL_SHORT             |  Open: ") +
          ORDER_STATUSES[sell_short_open_order.status],
      std::string("Profit: ") + ORDER_STATUSES[sell_short_profit_order.status],
      std::string("Stop Loss: ") +
          ORDER_STATUSES[sell_short_stop_loss_order.status],
  };

  std::cout << fmt.bold << fmt.cyan << std::endl;
  std::cout << utils::vector::join(buy_statuses, " • ") << std::endl;
  std::cout << utils::vector::join(sell_short_statuses, " • ") << std::endl;
  std::cout << fmt.reset;
}

#endif
