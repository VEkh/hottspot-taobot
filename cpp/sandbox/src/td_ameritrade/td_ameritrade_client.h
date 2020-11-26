#if !defined(TD_AMERITRADE_CLIENT)
#define TD_AMERITRADE_CLIENT

#include "deps/simdjson/simdjson.cpp" // simdjson::dom::parser
#include "utils/formatted.cpp" // Formatted::stream, Formatted::fmt_stream_t
#include <map>                 // std::map
#include <string>              // std::string

class TdAmeritradeClient {
public:
  void get_access_token();
  void get_quote(char *);
  void get_quote(std::string);
  void refresh_tokens();

  TdAmeritradeClient();

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

  std::string build_error_message(std::string message);
  void fetch_tokens(const std::map<std::string, std::string> body_params);
  void load_client_config();
  void load_tokens();
  void write_response_to_file(std::string content, const char *file_path);
};

#endif // TD_AMERITRADE_CLIENT
