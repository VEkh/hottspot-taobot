#ifndef ALPACA__MOCK__CLIENT_fetch_asset
#define ALPACA__MOCK__CLIENT_fetch_asset

#include "client.h" // Alpaca::Mock::Client
#include <string>   // std::string

std::string Alpaca::Mock::Client::fetch_asset() {
  return R"(
    {
      "easy_to_borrow": true,
      "shortable": true
    }
  )";
}

#endif
