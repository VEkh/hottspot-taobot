#ifndef OANDA__CLIENT
#define OANDA__CLIENT

#include "client.h" // Oanda::Client
#include "cancel_order.cpp"
#include "fetch_account.cpp"
#include "fetch_quote.cpp"
#include "load_config.cpp" // load_config
#include "parse_quote.cpp"

Oanda::Client::Client() { load_config(); }

#endif
