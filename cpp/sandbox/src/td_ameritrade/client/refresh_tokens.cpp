#if !defined TD_AMERITRADE__CLIENT_refresh_tokens
#define TD_AMERITRADE__CLIENT_refresh_tokens

#include "client.h"         // TdAmeritrade::Client, client_config, tokens
#include "fetch_tokens.cpp" // fetch_tokens
#include "load_tokens.cpp"  // load_tokens

void TdAmeritrade::Client::refresh_tokens() {
  load_tokens();

  fetch_tokens({
      {"grant_type", "refresh_token"},
      {"refresh_token", tokens.refresh_token},
  });
}
#endif
