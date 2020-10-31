#if !defined(TD_AMERITRADE_CLIENT)
#define TD_AMERITRADE_CLIENT

#include "../../deps/simdjson/simdjson.cpp" // simdjson::dom::parser
#include <string>                           // std::string

class TdAmeritradeClient {
private:
  simdjson::dom::parser json_parser;

public:
  void get_quote(std::string);
  void refresh_token();
};

#endif // TD_AMERITRADE_CLIENT
