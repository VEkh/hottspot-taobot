#if !defined(TD_AMERITRADE_CLIENT)
#define TD_AMERITRADE_CLIENT

#include "deps/simdjson/simdjson.cpp" // simdjson::dom::parser
#include <string>                     // std::string

class TdAmeritradeClient {
private:
  const char *TOKENS_PATH = "./config/td_ameritrade/tokens.json";

  simdjson::dom::parser json_parser;

  void write_response_to_file(std::string, const char *);

public:
  void get_acces_token();
  void get_quote(std::string);
  void refresh_token();
};

#endif // TD_AMERITRADE_CLIENT
