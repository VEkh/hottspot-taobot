#ifndef DB__STREAMED_QUOTE_result_to_quote
#define DB__STREAMED_QUOTE_result_to_quote

#include "lib/utils/string.cpp" // ::utils::string
#include "streamed_quote.h"     // DB::StreamedQuote, query_result_t, quote_t
#include <string>               // std::stod, std::string

DB::StreamedQuote::quote_t
DB::StreamedQuote::result_to_quote(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  quote_t out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "ask") {
        out.ask = std::stod(value);
      }

      if (field == "bid") {
        out.bid = std::stod(value);
      }

      if (field == "symbol") {
        out.symbol = value;
      }

      if (field == "timestamp") {
        out.timestamp = std::stod(value);
      }
    }

    out.price = (out.ask + out.bid) * 0.5;
  }

  return out;
}

#endif
