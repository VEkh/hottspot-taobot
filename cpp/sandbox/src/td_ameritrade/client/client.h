#if !defined(TD_AMERITRADE__CLIENT_H)
#define TD_AMERITRADE__CLIENT_H

#include "lib/formatted.cpp"      // Formatted::stream, Formatted::fmt_stream_t
#include "td_ameritrade/deps.cpp" // simdjson
#include <map>                    // std::map
#include <string>                 // std::string

namespace TdAmeritrade {
class Client {
public:
  void get_access_token();
  void get_quote(char *);
  void get_quote(std::string);
  void refresh_tokens();

  Client();

private:
  struct client_config_t {
    std::string client_id;
    std::string redirect_uri;
  } client_config;

  struct tokens_t {
    std::string access_token;
    std::string refresh_token;
  } tokens;

  const char *CONFIG_PATH = "./config/td_ameritrade/credentials.json";
  const char *TOKENS_PATH = "./config/td_ameritrade/tokens.json";
  simdjson::dom::parser json_parser;
  Formatted::fmt_stream_t stream_format = Formatted::stream();

  void fetch_tokens(const std::map<std::string, std::string> body_params);
  void load_client_config();
  void load_tokens();
  void write_response_to_file(std::string content, const char *file_path);
};
} // namespace TdAmeritrade

#endif
