#ifndef ALPACA__QUOTE_read_collection
#define ALPACA__QUOTE_read_collection

#include "alpaca/utils.cpp" // Alpaca::utils
#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include "quote.h"          // Alpaca::Quote, quote_t
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string
#include <vector>           // std::vector

void Alpaca::Quote::read_collection(const std::string symbol) {
  quote_t (*json_to_quote)(json &) = [](json &quote_json) -> quote_t {
    quote_t quote;
    quote.ask = quote_json["ask"];
    quote.bid = quote_json["bid"];
    quote.price = quote_json["price"];
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
    return;
  } catch (std::invalid_argument &) {
    return;
  }

  for (json quote_json : quotes_json) {
    this->quotes[symbol].push_back(json_to_quote(quote_json));
  }
}

#endif
