#if !defined(TD_AMERITRADE_CLIENT)
#define TD_AMERITRADE_CLIENT

#include "deps/simdjson/simdjson.cpp" // simdjson::dom::parser
#include <string>                     // std::string

class TdAmeritradeClient {
public:
  void get_acces_token();
  void get_quote(std::string);
  void refresh_token();

  TdAmeritradeClient();

private:
  struct client_config_t {
    std::string client_id;
    std::string redirect_uri;
  } client_config;

  const char *TOKENS_PATH = "./config/td_ameritrade/tokens.json";

  simdjson::dom::parser json_parser;

  void load_client_config();
  void write_response_to_file(std::string, const char *);
};

#endif // TD_AMERITRADE_CLIENT
