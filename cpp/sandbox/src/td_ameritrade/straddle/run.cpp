#if !defined TD_AMERITRADE__STRADDLE_run
#define TD_AMERITRADE__STRADDLE_run

#include "lib/formatted.cpp" // Formatted
#include "straddle.h"        // TdAmeritrade::Straddle, stream_format
#include "td_ameritrade/client/client.cpp" // TdAmeritrade::Client
#include <iostream>                        // std::cout, std::endl

void TdAmeritrade::Straddle::fetch_current_quote() {
  Formatted::fmt_stream_t fmt = stream_format;

  std::string quote = td_ameritrade_client.get_quote(symbol);

  std::cout << fmt.bold << fmt.yellow << symbol << fmt.reset
            << " quote: " << quote;
}

void TdAmeritrade::Straddle::log_start_message() {
  Formatted::fmt_stream_t fmt = stream_format;
  const char *shareString = quantity == 1 ? "share" : "shares";

  std::cout << fmt.bold << fmt.cyan << "Straddling " << fmt.yellow << quantity
            << fmt.cyan << " " << shareString << " of " << fmt.yellow << symbol
            << fmt.reset << std::endl;
}

void TdAmeritrade::Straddle::run() {
  log_start_message();
  fetch_current_quote();
}

#endif
