#if !defined TD_AMERITRADE__STRADDLE_run
#define TD_AMERITRADE__STRADDLE_run

#include "fetch_current_quote.cpp" // fetch_current_quote
#include "lib/formatted.cpp"       // Formatted
#include "straddle.h" // TdAmeritrade::Straddle, quantity, stream_format, symbol
#include <iostream>   // std::cout, std::endl

void TdAmeritrade::Straddle::log_start_message() {
  Formatted::fmt_stream_t fmt = stream_format;
  const char *shareString = quantity == 1 ? "share" : "shares";

  std::cout << fmt.bold << fmt.cyan << "Straddling " << fmt.blue << quantity
            << fmt.cyan << " " << shareString << " of " << fmt.blue << symbol
            << fmt.reset << std::endl;
}

void TdAmeritrade::Straddle::run() {
  log_start_message();
  fetch_current_quote();
  // calculate stop limit prices
}

#endif
