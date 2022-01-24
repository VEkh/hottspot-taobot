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
#include <map>    // std::map
#include <string> // std::string

Alpaca::Client::Client(std::map<std::string, std::string> flags_ = {}) {
  this->flags = flags_;
  load_config();
}

#endif
