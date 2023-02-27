#ifndef ALPACA__QUOTE_write_streamed
#define ALPACA__QUOTE_write_streamed

#include "lib/formatted.cpp"                   // Formatted
#include "lib/utils/io.cpp"                    // ::utils::io
#include "quote.h"                             // Alpaca::Quote, beast
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
    const std::string symbol = item["S"];

    const std::string filepath = std::string(DATA_DIR) +
                                 "/alpaca/streamed_quotes/" +
                                 std::string(symbol) + ".json";

    ::utils::io::write_to_file(item.dump(2), filepath.c_str());
  } catch (...) {
    Formatted::error_message(
        "❗ Something went wrong while trying to write streamed quote: " +
        stream.str());
    return;
  }
}

#endif
