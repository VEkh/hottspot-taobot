#if !defined ETRADE__STRADDLE_open
#define ETRADE__STRADDLE_open

#include "lib/formatted.cpp" // Formatted
#include "place_order.cpp"   // place_order
#include "straddle.h"        // ETrade::Straddle, stream_format
#include <iostream>          // std::cout, std::endl

void ETrade::Straddle::open() {
  Formatted::fmt_stream_t fmt = stream_format;

  place_order(sell_short_open_order);
  place_order(buy_open_order);

  std::cout << fmt.bold << fmt.green << std::endl;
  std::cout << "✅ Straddle successfully opened!" << std::endl;
  std::cout << fmt.reset;
}

#endif
