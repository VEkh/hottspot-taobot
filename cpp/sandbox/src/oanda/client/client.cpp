#ifndef OANDA__CLIENT
#define OANDA__CLIENT

#include "client.h" // Oanda::Client
#include "fetch_quote.cpp"
#include "load_config.cpp" // load_config
#include "parse_quote.cpp"

Oanda::Client::Client() { load_config(); }

#endif
