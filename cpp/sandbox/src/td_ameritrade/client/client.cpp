#if !defined TD_AMERITRADE__CLIENT
#define TD_AMERITRADE__CLIENT

#include "client.h" // TdAmeritrade::Client
#include "get_access_token.cpp"
#include "get_quote.cpp"
#include "load_client_config.cpp" // load_client_config
#include "place_order.cpp"
#include "refresh_tokens.cpp"

TdAmeritrade::Client::Client() { load_client_config(); }

TdAmeritrade::Client::Client(props_t props_) {
  props = props_;
  load_client_config();
}

#endif
