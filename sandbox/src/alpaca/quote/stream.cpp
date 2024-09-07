#ifndef ALPACA__QUOTE_stream
#define ALPACA__QUOTE_stream

/*
 * Alpaca::Quote
 * beast
 * http
 * net
 * ssl
 * websocket
 */
#include "quote.h"

#include "lib/utils/io.cpp"                   // ::utils::io
#include "lib/utils/string.cpp"               // ::utils::string
#include "lib/utils/websocket.cpp"            // ::utils::websocket
#include "src/deps.cpp"                       // json
#include "write_streamed.cpp"                 // write_streamed
#include <boost/asio/connect.hpp>             // boost::asio
#include <boost/asio/ip/tcp.hpp>              // boost::asio::ip::tcp
#include <boost/beast/core/flat_buffer.hpp>   // boost::beast::flat_buffer
#include <boost/beast/core/stream_traits.hpp> // boost::beast::get_lowest_layer
#include <boost/beast/http.hpp>               // boost::beast::http
#include <boost/beast/ssl.hpp>                // boost::asio::ssl
#include <boost/beast/ssl/ssl_stream.hpp>     // boost::beast::ssl_stream
#include <boost/beast/version.hpp>            // BOOST_BEAST_VERSION_STRING
#include <boost/beast/websocket.hpp>          // boost::beast::websocket
#include <boost/system/error_code.hpp>        // boost::system::error_code
#include <list>                               // std::list
#include <openssl/err.h>                      // ERR_get_error
#include <openssl/ssl.h>                      // SSL_set_tlsext_host_name
#include <sstream>                            // std::ostringstream
#include <string>                             // std::string, std::to_string
#include <time.h>                             // time

void Alpaca::Quote::stream(const std::list<std::string> &symbols) {
  net::io_context ioc;
  ssl::context ssl_context(ssl::context::tlsv12_client);
  tcp::resolver resolver(ioc);
  websocket::stream<beast::ssl_stream<tcp::socket>> ws(ioc, ssl_context);

  std::string host = "stream.data.alpaca.markets";
  const tcp::resolver::results_type results = resolver.resolve(host, "443");

  net::ip::basic_endpoint<tcp> endpoint =
      net::connect(beast::get_lowest_layer(ws), results);

  if (!SSL_set_tlsext_host_name(ws.next_layer().native_handle(),
                                host.c_str())) {
    throw beast::system_error(
        beast::error_code(static_cast<int>(::ERR_get_error()),
                          net::error::get_ssl_category()),
        "Failed to set SNI Hostname");
  }

  host += ":" + std::to_string(endpoint.port());

  ws.next_layer().handshake(ssl::stream_base::client);

  ws.set_option(websocket::stream_base::decorator(
      [](websocket::request_type &request) -> void {
        request.set(http::field::user_agent,
                    std::string(BOOST_BEAST_VERSION_STRING) +
                        " websocket-client-coro");
      }));

  beast::flat_buffer buffer;

  // ws.handshake(host, "/v1beta1/crypto");
  ws.handshake(host, "/v2/sip");
  ws.read(buffer);
  ::utils::websocket::log_and_consume_buffer(buffer);

  json auth_message = {
      {"action", "auth"},
      {"key", this->api_client.config.api_key_id},
      {"secret", this->api_client.config.api_secret_key},
  };

  ws.write(net::buffer(auth_message.dump()));
  ws.read(buffer);
  ::utils::websocket::log_and_consume_buffer(buffer);

  json subscribe_message = R"(
    { "action": "subscribe", "quotes": [] }
  )"_json;

  subscribe_message["quotes"] = symbols;

  ws.write(net::buffer(subscribe_message.dump()));
  ws.read(buffer);
  ::utils::websocket::log_and_consume_buffer(buffer);

  boost::system::error_code stream_error;

  const double now = time(nullptr);

  this->market_availability.set_market_close_epoch(now);
  this->market_availability.set_market_open_epoch(now, -30 * 60);

  bool is_market_open = this->market_availability.is_market_open(now);

  while (!stream_error && is_market_open) {
    try {
      ws.read(buffer, stream_error);
      write_streamed(buffer);
      ::utils::websocket::log_and_consume_buffer(buffer);

      is_market_open = this->market_availability.is_market_open(time(nullptr));
    } catch (boost::wrapexcept<boost::system::system_error> &) {
      puts("❌ Websocket Stream failed.");
      continue;
    }
  }

  if (!is_market_open) {
    std::cout << fmt.bold << fmt.cyan;
    printf("😴 Market is closed.\n");
    std::cout << fmt.reset;
  }

  ws.close(websocket::close_code::normal, stream_error);
}

#endif
