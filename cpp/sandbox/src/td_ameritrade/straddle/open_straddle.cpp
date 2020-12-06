#if !defined TD_AMERITRADE__STRADDLE__open_straddle
#define TD_AMERITRADE__STRADDLE__open_straddle

#include "build_order_open_payload.cpp" // build_order_open_payload
#include "lib/formatted.cpp"            // Formatted
#include "lib/utils/float.cpp"          // utils::float_
#include "straddle.h" // TdAmeritrade::Straddle, quantity, stream_format, symbol, td_ameritrade_client
#include "td_ameritrade/deps.cpp" // json
#include <iostream>               // std::cout, std::endl

void TdAmeritrade::Straddle::open_straddle() {
  Formatted::fmt_stream_t fmt = stream_format;

  json buy_order_payload = build_order_open_payload("BUY", order_prices.buy);
  json sell_short_order_payload =
      build_order_open_payload("SELL_SHORT", order_prices.sell_short);

  td_ameritrade_client.place_order(buy_order_payload);
  td_ameritrade_client.place_order(sell_short_order_payload);

  json close_limits;

  close_limits["BUY"] =
      utils::float_::to_currency(order_prices.buy.close_limit);
  close_limits["SELL_SHORT"] =
      utils::float_::to_currency(order_prices.sell_short.close_limit);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;

  std::cout << fmt.yellow << std::endl;
  std::cout << "Close with :" << close_limits.dump(2) << std::endl;
  std::cout << fmt.reset;
}

#endif
