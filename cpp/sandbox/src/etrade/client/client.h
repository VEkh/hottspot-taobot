#if !defined ETRADE__CLIENT_H
#define ETRADE__CLIENT_H

#include "lib/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <map>               // std::map
#include <string>            // std::string

namespace ETrade {
class Client {
public:
  enum debug_t { OFF, ON };

  struct props_t {
    debug_t debug_flag;
  };

  void fetch_access_token();

  Client();
  Client(props_t);

private:
  struct client_config_t {
    std::string account_id;
    std::string oauth_consumer_key;
    std::string oauth_consumer_secret;
    std::string oauth_token;
    std::string oauth_token_secret;
    std::string oauth_verifier;
  } client_config;

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  const char *CONFIG_PATH = "./config/etrade/credentials.json";
  const char *TOKENS_PATH = "./config/etrade/tokens.json";

  props_t props = {
      .debug_flag = debug_t::OFF,
  };

  std::string build_request_header(std::string,
                                   std::map<std::string, std::string>);
  void authorized_fetch_access_token();
  void fetch_request_token();
  void load_client_config();
  void write_response_to_file(std::string, const char *);
};
} // namespace ETrade

#endif
