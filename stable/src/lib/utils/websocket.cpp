#ifndef UTILS__WEBSOCKET
#define UTILS__WEBSOCKET

#include <boost/beast/core/flat_buffer.hpp> // boost::beast, boost::beast::flat_buffer
#include <boost/beast/core/make_printable.hpp> // boost::beast::make_printable

namespace utils {
namespace websocket {
namespace beast = boost::beast;
namespace net = boost::asio;

void log_and_consume_buffer(beast::flat_buffer &buffer) {
  Formatted::fmt_stream_t fmt = Formatted::stream();

  std::cout << fmt.bold << fmt.yellow;
  std::cout << beast::make_printable(buffer.data()) << std::endl;
  std::cout << fmt.reset;

  buffer.consume(buffer.size());
}

void log_write_buffer(const net::const_buffer buffer) {
  const char *buff_chars = static_cast<const char *>(buffer.data());
  std::cout << buff_chars << std::endl;
}
} // namespace websocket
} // namespace utils

#endif
