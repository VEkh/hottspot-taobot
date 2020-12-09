#if !defined(ETRADE__CLIENT_H)
#define ETRADE__CLIENT_H

#include "lib/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <string>            // std::string

namespace ETrade {
class Client {
public:
  enum debug_t { OFF, ON };

  struct props_t {
    debug_t debug_flag;
  };

  void get_access_token();

  Client();
  Client(props_t);

private:
  struct client_config_t {
    std::string account_id;
    std::string oauth_consumer_key;
    std::string oauth_consumer_secret;
  } client_config;

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  const char *CONFIG_PATH = "./config/etrade/credentials.json";

  props_t props = {
      .debug_flag = debug_t::OFF,
  };

  void load_client_config();
};
} // namespace ETrade

#endif
