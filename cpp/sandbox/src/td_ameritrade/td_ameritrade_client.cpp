#if !defined TD_AMERITRADE_CLIENT
#define TD_AMERITRADE_CLIENT

#include "td_ameritrade_client.h" // TdAmeritradeClient
#include "get_access_token.cpp"
#include "get_quote.cpp"
#include "load_client_config.cpp" // load_client_config
#include "refresh_tokens.cpp"

TdAmeritradeClient::TdAmeritradeClient() { load_client_config(); }

#endif
