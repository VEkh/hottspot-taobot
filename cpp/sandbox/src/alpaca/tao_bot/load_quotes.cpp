#ifndef ALPACA__TAO_BOT_load_quotes
#define ALPACA__TAO_BOT_load_quotes

#include "alpaca/utils.cpp" // Alpaca::utils
#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include "tao_bot.h"        // Alpaca::TaoBot, quote_t
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string
#include <vector>           // std::vector

void Alpaca::TaoBot::load_quotes(const std::string &symbol_) {
  quote_t (*json_to_quote)(json &) = [](json &quote_json) -> quote_t {
    quote_t quote;
    quote.ask = quote_json["ask"];
    quote.bid = quote_json["bid"];
    quote.price = quote_json["price"];
    quote.timestamp = quote_json["timestamp"];

    return quote;
  };

  const std::string filepath = std::string(APP_DIR) + "/data/alpaca/quotes/" +
                               std::string(symbol_) + ".json";

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
    this->quotes[symbol_].push_back(json_to_quote(quote_json));
  }
}

#endif
