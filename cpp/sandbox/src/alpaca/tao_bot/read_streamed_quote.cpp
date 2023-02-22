#ifndef ALPACA__TAO_BOT_read_streamed_quote
#define ALPACA__TAO_BOT_read_streamed_quote

#include "deps.cpp"           // json, nlohmann
#include "lib/formatted.cpp"  // Formatted
#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Alpaca::TaoBot, quote_t
#include <ctime>              // std::tm, std::mktime
#include <fstream>            // std::ifstream
#include <stdexcept>          // std::domain_error
#include <string>             // std::string

Alpaca::TaoBot::quote_t Alpaca::TaoBot::read_streamed_quote() {
  const std::string filepath = std::string(DATA_DIR) +
                               "/alpaca/streamed_quotes/" +
                               std::string(this->symbol) + ".json";

  std::ifstream file;
  json quote_json;

  try {
    file = ::utils::io::read_file(filepath.c_str());
    file >> quote_json;
    file.close();
  } catch (nlohmann::detail::parse_error &) {
    return read_streamed_quote();
  }

  json wrapper;
  wrapper["quote"] = quote_json;
  quote_t parsed_quote = this->api_client.parse_quote(wrapper.dump());
  parsed_quote.symbol = this->symbol;

  std::tm parsed_time =
      ::utils::time_::parse_timestamp(quote_json["t"], "%Y-%m-%dT%H:%M:%SZ");

  const std::time_t quote_epoch = std::mktime(&parsed_time);
  const std::time_t now = std::time(nullptr);

  if ((now - quote_epoch) > 10) {
    const std::string error_message = Formatted::error_message(
        this->symbol + std::string(" quote stale. Falling back to fetch."));

    throw std::domain_error(error_message);
  }

  return parsed_quote;
}

#endif
