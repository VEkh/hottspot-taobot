#if !defined TD_AMERITRADE__STRADDLE_condensed_quote
#define TD_AMERITRADE__STRADDLE_condensed_quote

#include "straddle.h" // TdAmeritrade::Straddle, quote, symbol
#include <string>     // std::string

std::string TdAmeritrade::Straddle::condensed_quote() { return quote; }

#endif
