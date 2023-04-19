#ifndef OANDA__TAO_BOT_write_quotes
#define OANDA__TAO_BOT_write_quotes

#include "deps.cpp"          // json
#include "lib/formatted.cpp" // Formatted
#include "lib/utils/io.cpp"  // utils::io
#include "tao_bot.h"         // Oanda::TaoBot, quote_t
#include <iostream>          // std::cout, std::endl
#include <list>              // std::list
#include <stdexcept>         // std::invalid_argument
#include <string>            // std::string
#include <vector>            // std::vector

void Oanda::TaoBot::write_quotes() {
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

    const std::string filepath = std::string(DATA_DIR) + "/oanda/quotes/" +
                                 std::string(this->symbol) + ".json";

    const int sample_size = this->QUOTES_MAX_SIZE;
    int i = 0;
    json quotes_json;
    std::list<json> quotes_list;
    std::vector<quote_t>::reverse_iterator it;

    for (it = this->quotes.rbegin();
         it != this->quotes.rend() && i < sample_size; it++, i++) {
      quotes_list.push_front(quote_to_json(*it));
    }

    quotes_json = quotes_list;

    this->db_quote.upsert(this->quotes.back());

    ::utils::io::write_to_file(quotes_json.dump(2), filepath.c_str());
  } catch (nlohmann::detail::parse_error &) {
    std::string error_message =
        Formatted::error_message(std::string("OANDA__TAO_BOT_write_quotes") +
                                 ": Parse error while writing quotes.");

    throw(std::invalid_argument(error_message));
  }
}

#endif
