#ifndef ALPACA__QUOTE_H
#define ALPACA__QUOTE_H

#include "alpaca/client/client.cpp"         // Alpaca::Client
#include "alpaca/types.cpp"                 // Alpaca::t
#include "lib/formatted.cpp"                // Formatted
#include "lib/pg/pg.cpp"                    // Pg
#include "models/quote/quote.cpp"           // DB::Quote
#include "types.cpp"                        // Global::t
#include <boost/asio/connect.hpp>           // boost::asio
#include <boost/beast/core/flat_buffer.hpp> // boost::beast::flat_buffer
#include <boost/beast/http.hpp>             // boost::beast, boost::beast::http
#include <boost/beast/ssl.hpp>              // boost::asio::ssl
#include <boost/beast/websocket.hpp>        // boost::beast::websocket
#include <map>                              // std::map
#include <string>                           // std::string
#include <vector>                           // std::vector

namespace Alpaca {
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace websocket = beast::websocket;

class Quote {
public:
  using price_movement_t = Global::t::price_movement_t;
  using quote_t = Global::t::quote_t;
  using tcp = net::ip::tcp;

  Quote(std::map<std::string, std::string>);

  price_movement_t read_price_movement(const std::string);
  std::vector<quote_t> read_collection(const std::string, const double);
  void stream(int, char *[]);
  void watch(const std::vector<std::string>);

private:
  Alpaca::Client api_client;
  DB::Quote db_quote;
  Pg pg;
  Formatted::fmt_stream_t fmt = Formatted::stream();
  const double AVG_ONE_SEC_VARIANCE_TIMEFRAME = 3.0 * 60.0;
  const int PRICE_MOVEMENT_SAMPLE_SIZE = 5e5;
  const int QUOTES_MAX_SIZE = 8e3;
  std::map<std::string, std::string> flags;
  std::map<std::string, price_movement_t> price_movements;
  std::map<std::string, std::vector<quote_t>> quotes;

  double current_price(const std::string);

  quote_t fetch_quote(const std::string);
  quote_t get_quote(const std::string);
  quote_t read_streamed_quote(const std::string);

  void fetch_and_persist_quote(const std::string, const bool);
  void initialize(std::map<std::string, std::string>);
  void read(const std::string);
  void set_and_persist_price_movement(const std::string);
  void set_price_movement(const std::string);
  void write();
  void write_collection(const std::string);
  void write_price_movement(const std::string);
  void write_streamed(const beast::flat_buffer &);
};
} // namespace Alpaca

#endif
