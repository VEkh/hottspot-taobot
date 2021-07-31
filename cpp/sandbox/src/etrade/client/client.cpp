#ifndef ETRADE__CLIENT
#define ETRADE__CLIENT

#include "client.h" // ETrade::Client
#include "cancel_order.cpp"
#include "fetch.cpp"
#include "fetch_access_token.cpp"
#include "fetch_account_balance.cpp"
#include "fetch_order.cpp"
#include "fetch_quote.cpp"
#include "load_client_config.cpp" // load_client_config
#include "parse_quote.cpp"
#include "place_order.cpp"
#include "post.cpp"
#include "refresh_token.cpp"

ETrade::Client::Client() { load_client_config(); }

ETrade::Client::Client(props_t props_) {
  props = props_;
  load_client_config();
}

#endif
