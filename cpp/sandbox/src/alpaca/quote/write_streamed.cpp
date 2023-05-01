#ifndef ALPACA__QUOTE_write_streamed
#define ALPACA__QUOTE_write_streamed

#include "lib/formatted.cpp"                        // Formatted
#include "db/streamed_quote/streamed_quote.cpp" // DB::StreamedQuote
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

    const quote_t quote = this->api_client.parse_quote(wrapper.dump());

    this->db_streamed_quote.upsert({
        .ask = quote.ask,
        .bid = quote.bid,
        .symbol = symbol,
        .debug = true,
    });
  } catch (...) {
    const std::string error_message = Formatted::error_message(
        "❗ Something went wrong while trying to write streamed quote: " +
        stream.str());

    puts(error_message.c_str());

    return;
  }
}

#endif
