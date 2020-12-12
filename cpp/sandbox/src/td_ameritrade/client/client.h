#if !defined(TD_AMERITRADE__CLIENT_H)
#define TD_AMERITRADE__CLIENT_H

#include "lib/formatted.cpp"      // Formatted::stream, Formatted::fmt_stream_t
#include "td_ameritrade/deps.cpp" // json
#include <map>                    // std::map
#include <string>                 // std::string

namespace TdAmeritrade {
class Client {
public:
  enum debug_t { OFF, ON };

  struct props_t {
    debug_t debug_flag;
  };

  std::string get_quote(char *);
  std::string get_quote(std::string);
  void fetch_access_token();
  void place_order(json);
  void refresh_tokens();

  Client();
  Client(props_t);

private:
  struct client_config_t {
    int account_id;
    std::string client_id;
    std::string redirect_uri;
  } client_config;

  struct tokens_t {
    std::string access_token;
    std::string refresh_token;
  } tokens;

  Formatted::fmt_stream_t stream_format = Formatted::stream();
  const char *CONFIG_PATH = "./config/td_ameritrade/credentials.json";
  const char *TOKENS_PATH = "./config/td_ameritrade/tokens.json";

  props_t props = {
      .debug_flag = debug_t::OFF,
  };

  void fetch_tokens(const std::map<std::string, std::string> body_params);
  void load_client_config();
  void load_tokens();
  void write_response_to_file(std::string content, const char *file_path);
};
} // namespace TdAmeritrade

#endif
