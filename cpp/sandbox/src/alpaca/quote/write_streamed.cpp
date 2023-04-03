#ifndef ALPACA__QUOTE_write_streamed
#define ALPACA__QUOTE_write_streamed

#include "lib/formatted.cpp"                        // Formatted
#include "lib/utils/io.cpp"                         // ::utils::io
#include "models/streamed_quote/streamed_quote.cpp" // DB::StreamedQuote
#include "quote.h"                             // Alpaca::Quote, beast, quote_t
#include "src/deps.cpp"                        // json
#include <boost/beast/core/flat_buffer.hpp>    // boost::beast::flat_buffer
#include <boost/beast/core/make_printable.hpp> // boost::beast::make_printable
#include <sstream>                             // std::ostringstream
#include <string>                              // std::string, std::to_string

void Alpaca::Quote::write_streamed(const beast::flat_buffer &buffer) {
  std::ostringstream stream;

  stream << beast::make_printable(buffer.data());

  try {
    json resp_json = json::parse(stream.str());
    json item = resp_json[0];
    json wrapper;

    wrapper["quote"] = item;
    const std::string symbol = item["S"];

    const std::string filepath = std::string(DATA_DIR) +
                                 "/alpaca/streamed_quotes/" +
                                 std::string(symbol) + ".json";

    ::utils::io::write_to_file(item.dump(2), filepath.c_str());

    const quote_t quote = this->api_client.parse_quote(wrapper.dump());

    this->db_streamed_quote.upsert({
        .ask = quote.ask,
        .bid = quote.bid,
        .symbol = symbol,
        .debug = true,
    });
  } catch (...) {
    Formatted::error_message(
        "❗ Something went wrong while trying to write streamed quote: " +
        stream.str());
    return;
  }
}

#endif
