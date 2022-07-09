#ifndef ALPACA__CLIENT_H
#define ALPACA__CLIENT_H

#include "alpaca/types.cpp"                 // Alpaca::t
#include "lib/curl_client/curl_client.cpp"  // CurlClient
#include "lib/formatted.cpp"                // Formatted
#include "types.cpp"                        // Global::t
#include <boost/asio/connect.hpp>           // boost::asio
#include <boost/beast/core/flat_buffer.hpp> // boost::beast::flat_buffer
#include <boost/beast/http.hpp>             // boost::beast, boost::beast::http
#include <boost/beast/ssl.hpp>              // boost::asio::ssl
#include <boost/beast/websocket.hpp>        // boost::beast::websocket
#include <map>                              // std::map
#include <string>                           // std::string

namespace Alpaca {
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
namespace websocket = beast::websocket;

class Client {
public:
  using order_action_t = Alpaca::t::order_action_t;
  using order_status_t = Alpaca::t::order_status_t;
  using order_t = Alpaca::t::order_t;
  using order_type_t = Alpaca::t::order_type_t;
  using post_params_t = CurlClient::post_params_t;
  using quote_t = Alpaca::t::quote_t;
  using tcp = net::ip::tcp;

  Client(std::map<std::string, std::string> = {});

  CurlClient place_order(order_t *order);

  std::string cancel_order(const std::string &);
  std::string cancel_order(const order_t *order);
  std::string fetch_account();
  std::string fetch_order(const std::string &);
  std::string fetch_quote(char *);
  std::string fetch_quote(const std::string &);

  quote_t parse_quote(const std::string &);

  void stream_quotes(int, char *[]);

private:
  struct config_t {
    std::string api_key_id;
    std::string api_secret_key;
    std::string base_url;
    std::string data_base_url;
  } config;

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::map<std::string, std::string> flags = {
      {"hedge", "0"},
      {"paper", "0"},
  };

  CurlClient fetch(std::string);
  CurlClient post(const post_params_t params);
  bool is_live();
  void load_config();
  void write_streamed_quote(const beast::flat_buffer &);
};
} // namespace Alpaca

#endif
