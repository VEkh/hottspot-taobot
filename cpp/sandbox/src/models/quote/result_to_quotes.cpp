#ifndef DB__QUOTE_result_to_quotes
#define DB__QUOTE_result_to_quotes

#include "lib/utils/string.cpp" // ::utils::string
#include "quote.h"              // DB::Quote, query_result_t, quote_t
#include <string>               // std::stod, std::string
#include <vector>               // std::vector

std::vector<DB::Quote::quote_t>
DB::Quote::result_to_quotes(const query_result_t &result) {
  const std::vector<std::string> fields = result.fields;
  const std::vector<std::string> tuples = result.tuples;
  std::vector<quote_t> out;

  for (std::vector<std::string>::const_iterator it = tuples.begin();
       it != tuples.end(); it++) {
    const std::vector<std::string> values = ::utils::string::split(*it, ",");
    quote_t quote;

    for (int i = 0; i < result.fields_n; i++) {
      const std::string field = fields.at(i);
      const std::string value = values.at(i);

      if (field == "ask") {
        quote.ask = std::stod(value);
      }

      if (field == "bid") {
        quote.bid = std::stod(value);
      }

      if (field == "symbol") {
        quote.symbol = value;
      }

      if (field == "timestamp" || field == "timestamp_epoch") {
        quote.timestamp = std::stod(value);
      }
    }

    quote.price = (quote.ask + quote.bid) * 0.5;
    out.push_back(quote);
  }

  return out;
}

#endif
