#ifndef OANDA__TAO_BOT_load_quotes
#define OANDA__TAO_BOT_load_quotes

#include "deps.cpp"         // json, nlohmann
#include "lib/utils/io.cpp" // ::utils::io
#include "oanda/utils.cpp"  // Oanda::utils
#include "tao_bot.h"        // Oanda::TaoBot, quote_t
#include <fstream>          // std::ifstream
#include <stdexcept>        // std::invalid_argument
#include <string>           // std::string
#include <vector>           // std::vector

void Oanda::TaoBot::load_quotes() {
  quote_t (*json_to_quote)(json &) = [](json &quote_json) -> quote_t {
    quote_t quote;
    quote.ask = quote_json["ask"];
    quote.bid = quote_json["bid"];
    quote.price = quote_json["price"];
    quote.timestamp = quote_json["timestamp"];

    return quote;
  };

  const std::string filepath = std::string(APP_DIR) + "/data/oanda/quotes/" +
                               std::string(this->symbol) + ".json";

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
    this->quotes.push_back(json_to_quote(quote_json));
  }
}

#endif
