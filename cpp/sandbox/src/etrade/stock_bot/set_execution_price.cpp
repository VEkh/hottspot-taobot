#if !defined ETRADE__STOCK_BOT_set_execution_price
#define ETRADE__STOCK_BOT_set_execution_price

#include "etrade/deps.cpp"    // json
#include "get_order_json.cpp" // get_order_json
#include "lib/formatted.cpp"  // Formatted
#include "stock_bot.h" // ETrade::StockBot, order_t, simple_moving_average
#include <iostream>    // std::cout, std::endl

void ETrade::StockBot::set_execution_price(order_t *order) {
  Formatted::fmt_stream_t fmt = stream_format;
  json order_json = get_order_json(*order);

  if (order_json.empty() ||
      !order_json["OrderDetail"][0]["Instrument"][0].contains(
          "averageExecutionPrice")) {
    std::cout << fmt.bold << fmt.red;
    std::cout << "❌ Execution price not present in order: " << order_json.dump()
              << std::endl;
    std::cout << fmt.reset;
    return;
  }

  order->execution_price =
      order_json["OrderDetail"][0]["Instrument"][0]["averageExecutionPrice"];

  order->sma_execution_price = simple_moving_average;
}

#endif
