#if !defined ETRADE__CLIENT
#define ETRADE__CLIENT

#include "client.h" // ETrade::Client
#include "fetch.cpp"
#include "fetch_access_token.cpp"
#include "fetch_quote.cpp"
#include "load_client_config.cpp" // load_client_config
#include "post.cpp"
#include "refresh_token.cpp"

ETrade::Client::Client() { load_client_config(); }

ETrade::Client::Client(props_t props_) {
  props = props_;
  load_client_config();
}

#endif
