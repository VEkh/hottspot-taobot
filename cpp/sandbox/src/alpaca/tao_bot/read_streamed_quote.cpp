#ifndef ALPACA__TAO_BOT_read_streamed_quote
#define ALPACA__TAO_BOT_read_streamed_quote

#include "deps.cpp"  // json, nlohmann
#include "tao_bot.h" // Alpaca::TaoBot, quote_t
#include <fstream>   // std::ifstream
#include <string>    // std::string

Alpaca::TaoBot::quote_t
Alpaca::TaoBot::read_streamed_quote(const std::string symbol_) {
  const std::string filepath = std::string(APP_DIR) +
                               "/data/alpaca/streamed_quotes/" +
                               std::string(symbol_) + ".json";

  std::ifstream file;
  json quote_json;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> quote_json;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
    return read_streamed_quote(symbol_);
  }

  json wrapper;
  wrapper["quote"] = quote_json;
  quote_t parsed_quote = this->api_client.parse_quote(wrapper.dump());
  parsed_quote.symbol = symbol_;

  return parsed_quote;
}

#endif
