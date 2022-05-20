#ifndef ALPACA__CLIENT_write_streamed_quote
#define ALPACA__CLIENT_write_streamed_quote

#include "client.h"                            // Alpaca::Client, beast
#include "lib/formatted.cpp"                   // Formatted
#include "lib/utils/io.cpp"                    // ::utils::io
#include "src/deps.cpp"                        // json
#include <boost/beast/core/flat_buffer.hpp>    // boost::beast::flat_buffer
#include <boost/beast/core/make_printable.hpp> // boost::beast::make_printable
#include <sstream>                             // std::ostringstream
#include <string>                              // std::string, std::to_string

void Alpaca::Client::write_streamed_quote(const beast::flat_buffer &buffer) {
  std::ostringstream stream;

  stream << beast::make_printable(buffer.data());

  try {
    json resp_json = json::parse(stream.str());
    json item = resp_json[0];
    const std::string symbol = item["S"];

    const std::string filepath = std::string(APP_DIR) +
                                 "/data/alpaca/streamed_quotes/" +
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
