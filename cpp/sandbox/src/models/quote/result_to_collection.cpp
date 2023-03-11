#ifndef DB__QUOTE_result_to_collection
#define DB__QUOTE_result_to_collection

#include "lib/utils/time.cpp" // ::utils::time_
#include "quote.h"            // DB::Quote, query_result_t, quote_t
#include <string>             // std::string
#include <vector>             // std::vector

#include <ctime> // std::tm

std::vector<DB::Quote::quote_t>
DB::Quote::result_to_collection(const query_result_t &result) {
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

      if (field == "timestamp") {
        quote.timestamp = std::stod(value) * 1000;
      }
    }

    quote.price = (quote.ask + quote.bid) * 0.5;
    out.push_back(quote);
  }

  return out;
}

#endif
