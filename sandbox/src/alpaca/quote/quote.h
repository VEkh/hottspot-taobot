#ifndef ALPACA__QUOTE_H
#define ALPACA__QUOTE_H

#include "alpaca/client/client.cpp"                    // Alpaca::Client
#include "alpaca/types.cpp"                            // Alpaca::t
#include "db/quote/quote.cpp"                          // DB::Quote
#include "db/streamed_quote/streamed_quote.cpp"        // DB::StreamedQuote
#include "lib/formatted.cpp"                           // Formatted
#include "lib/nyse_availability/nyse_availability.cpp" // NyseAvailability
#include "lib/pg/pg.cpp"                               // Pg
#include "types.cpp"                                   // Global::t
#include <boost/asio/connect.hpp>                      // boost::asio
#include <boost/beast/core/flat_buffer.hpp> // boost::beast::flat_buffer
#include <boost/beast/http.hpp>             // boost::beast, boost::beast::http
#include <boost/beast/ssl.hpp>              // boost::asio::ssl
#include <boost/beast/websocket.hpp>        // boost::beast::websocket
#include <list>                             // std::list
#include <map>                              // std::map
#include <string>                           // std::string

namespace Alpaca {
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace websocket = beast::websocket;

class Quote {
public:
  using quote_t = Global::t::quote_t;
  using tcp = net::ip::tcp;

  Quote(){};
  Quote(Pg, std::map<std::string, std::string>);
  Quote(std::map<std::string, std::string>);

  DB::Quote db_quote;

  void stream(const std::list<std::string> &);
  void watch(const std::list<std::string> &);

private:
  Alpaca::Client api_client;
  DB::StreamedQuote db_streamed_quote;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  NyseAvailability market_availability;
  Pg pg;
  std::map<std::string, quote_t> current_quotes;
  std::map<std::string, quote_t> previous_quotes;
  std::map<std::string, std::string> flags;

  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);
  quote_t get_streamed_quote(const std::string);

  void fetch_and_persist_quote(const std::string, const bool);
  void read(const std::string);
  void write();
  void write_streamed(const beast::flat_buffer &);
};
} // namespace Alpaca

#endif
