#ifndef ALPACA__CLIENT_is_live
#define ALPACA__CLIENT_is_live

#include "client.h" // Alpaca::Client
#include <string>   // std::stoi

bool Alpaca::Client::is_live() {
  return this->flags["paper"].empty()
             ? true
             : !((bool)std::stoi(this->flags["paper"]));
}

#endif
