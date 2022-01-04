#ifndef ALPACA__CLIENT
#define ALPACA__CLIENT

#include "client.h" // Alpaca::Client
#include "cancel_order.cpp"
#include "fetch_account.cpp"
#include "fetch_order.cpp"
#include "fetch_quote.cpp"
#include "load_config.cpp" // load_config
#include "parse_quote.cpp"
#include "place_order.cpp"

Alpaca::Client::Client() { load_config(); }

#endif
