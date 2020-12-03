#if !defined TD_AMERITRADE__STRADDLE_fetch_current_quote
#define TD_AMERITRADE__STRADDLE_fetch_current_quote

#include "condensed_quote.cpp" // condensed_quote
#include "lib/formatted.cpp"   // Formatted
#include "straddle.h" // TdAmeritrade::Straddle, stream_format, symbol, td_ameritrade_client
#include <iostream> // std::cout, std::endl

void TdAmeritrade::Straddle::fetch_current_quote() {
  Formatted::fmt_stream_t fmt = stream_format;

  quote = td_ameritrade_client.get_quote(symbol);

  std::cout << fmt.bold << fmt.yellow << symbol << " quote: " << fmt.reset
            << condensed_quote();
}

#endif
