#ifndef ALPACA__QUOTE_read_collection
#define ALPACA__QUOTE_read_collection

#include "alpaca/utils.cpp" // Alpaca::utils
#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include "quote.h"          // Alpaca::Quote, quote_t
#include <fstream>          // std::ifstream
#include <math.h>           // INFINITY
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string
#include <vector>           // std::vector

std::vector<Alpaca::Quote::quote_t>
Alpaca::Quote::read_collection(const std::string symbol,
                               const double limit = INFINITY) {
  quote_t (*json_to_quote)(json &) = [](json &quote_json) -> quote_t {
    quote_t quote;
    quote.ask = quote_json["ask"];
    quote.bid = quote_json["bid"];
    quote.price = quote_json["price"];
    quote.symbol = quote_json["symbol"];
    quote.timestamp = quote_json["timestamp"];

    return quote;
  };

  const std::string filepath =
      std::string(DATA_DIR) + "/alpaca/quotes/" + symbol + ".json";

  std::ifstream file;
  json quotes_json;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> quotes_json;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
    return {};
  } catch (std::invalid_argument &) {
    return {};
  }

  try {
    for (json quote_json : quotes_json) {
      this->quotes[symbol].push_back(json_to_quote(quote_json));
    }
  } catch (nlohmann::detail::type_error &) {
    return read_collection(symbol, limit);
  }

  std::vector<quote_t>::iterator range_begin =
      limit == INFINITY ? this->quotes[symbol].begin()
                        : this->quotes[symbol].end() - limit;

  return std::vector<quote_t>(range_begin, this->quotes[symbol].end());
}

#endif
