#ifndef ETRADE__CLIENT_refresh_token
#define ETRADE__CLIENT_refresh_token

#include "client.h"        // ETrade::Client, config
#include "fetch_token.cpp" // fetch_token
#include "load_token.cpp"  // load_token

void ETrade::Client::refresh_token() {
  load_token();
  fetch_token(config.base_url + "/oauth/renew_access_token");
}
#endif
