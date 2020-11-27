#if !defined TD_AMERITRADE_CLIENT__REFRESH_TOKENS
#define TD_AMERITRADE_CLIENT__REFRESH_TOKENS

#include "fetch_tokens.cpp"       // fetch_tokens
#include "load_tokens.cpp"        // load_tokens
#include "td_ameritrade_client.h" // TdAmeritradeClient, client_config, tokens

void TdAmeritradeClient::refresh_tokens() {
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
