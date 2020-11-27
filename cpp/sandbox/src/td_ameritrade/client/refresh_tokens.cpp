#if !defined TD_AMERITRADE__CLIENT_refresh_tokens
#define TD_AMERITRADE__CLIENT_refresh_tokens

#include "client.h"         // TdAmeritrade::Client, client_config, tokens
#include "fetch_tokens.cpp" // fetch_tokens
#include "load_tokens.cpp"  // load_tokens

void TdAmeritrade::Client::refresh_tokens() {
  load_tokens();

  fetch_tokens({
      {"access_type", "offline"},
      {"client_id", client_config.client_id},
      {"grant_type", "refresh_token"},
      {"redirect_uri", client_config.redirect_uri},
      {"refresh_token", tokens.refresh_token},
  });
}
#endif
