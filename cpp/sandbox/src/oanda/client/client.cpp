#ifndef OANDA__CLIENT
#define OANDA__CLIENT

#include "client.h" // Oanda::Client
#include "cancel_order.cpp"
#include "fetch_account.cpp"
#include "fetch_instruments.cpp"
#include "fetch_order.cpp"
#include "fetch_quote.cpp"
#include "fetch_trade.cpp"
#include "load_config.cpp" // load_config
#include "map_margin_rates.cpp"
#include "parse_quote.cpp"
#include "place_order.cpp"
#include "stream_account.cpp"
#include <map>    // std::map
#include <string> // std::string

Oanda::Client::Client(std::map<std::string, std::string> flags_) {
  this->flags = flags_;
  load_config();
}

#endif
