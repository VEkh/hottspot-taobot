#ifndef ALPACA__QUOTE_write_collection
#define ALPACA__QUOTE_write_collection

#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted
#include "lib/utils/io.cpp"  // utils::io
#include "quote.h"           // Alpaca::Quote, quote_t
#include <iostream>          // std::cout, std::endl
#include <list>              // std::list
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string
#include <vector>            // std::vector

void Alpaca::Quote::write_collection(const std::string symbol) {
  try {
    json (*quote_to_json)(quote_t &) = [](quote_t &quote) -> json {
      return {
          {"ask", quote.ask},
          {"bid", quote.bid},
          {"price", quote.price},
          {"symbol", quote.symbol},
          {"timestamp", quote.timestamp},
      };
    };

    const std::string filepath =
        std::string(DATA_DIR) + "/alpaca/quotes/" + symbol + ".json";

    const int sample_size = this->QUOTES_MAX_SIZE;
    int i = 0;
    json quotes_json;
    std::list<json> quotes_list;
    std::vector<quote_t>::reverse_iterator it;

    for (it = this->quotes[symbol].rbegin();
         it != this->quotes[symbol].rend() && i < sample_size; it++, i++) {
      quotes_list.push_front(quote_to_json(*it));
    }

    quotes_json = quotes_list;

    ::utils::io::write_to_file(quotes_json.dump(2), filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message =
        Formatted::error_message(std::string("ALPACA__QUOTE_write_collection") +
                                 ": Parse error while writing quotes.");

    throw(std::invalid_argument(error_message));
  }
}

#endif
