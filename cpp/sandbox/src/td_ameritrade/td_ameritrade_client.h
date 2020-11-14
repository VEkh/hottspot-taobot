#if !defined(TD_AMERITRADE_CLIENT)
#define TD_AMERITRADE_CLIENT

#include "deps/simdjson/simdjson.cpp" // simdjson::dom::parser
#include "utils/stream_formatter.cpp" // StreamFormatter, StreamFormatter::code_t
#include <map>                        // std::map
#include <string>                     // std::string

class TdAmeritradeClient {
public:
  void get_access_token();
  void get_quote(std::string symbol);
  void refresh_tokens();

  TdAmeritradeClient();

private:
  struct client_config_t {
    std::string client_id;
    std::string redirect_uri;
  } client_config;

  struct stream_format_t {
    StreamFormatter cyan;
    StreamFormatter green;
    StreamFormatter red;
    StreamFormatter reset;
    StreamFormatter yellow;
  } stream_format = {
      .cyan = StreamFormatter({
          StreamFormatter::code_t::FONT_BOLD,
          StreamFormatter::code_t::FG_CYAN,
      }),
      .green = StreamFormatter({
          StreamFormatter::code_t::FONT_BOLD,
          StreamFormatter::code_t::FG_GREEN,
      }),
      .red = StreamFormatter({
          StreamFormatter::code_t::FONT_BOLD,
          StreamFormatter::code_t::FG_RED,
      }),
      .reset = StreamFormatter({StreamFormatter::code_t::RESET}),
      .yellow = StreamFormatter({
          StreamFormatter::code_t::FONT_BOLD,
          StreamFormatter::code_t::FG_YELLOW,
      }),
  };

  struct tokens_t {
    std::string access_token;
    std::string refresh_token;
  } tokens;

  const char *CONFIG_PATH = "./config/td_ameritrade/credentials.json";
  const char *TOKENS_PATH = "./config/td_ameritrade/tokens.json";

  simdjson::dom::parser json_parser;

  std::string build_error_message(std::string message);
  void fetch_tokens(const std::map<std::string, std::string> body_params);
  void load_client_config();
  void load_tokens();
  void write_response_to_file(std::string content, const char *file_path);
};

#endif // TD_AMERITRADE_CLIENT
