#ifndef ALPACA__CLIENT_is_hedging
#define ALPACA__CLIENT_is_hedging

#include "client.h" // Alpaca::Client
#include <string>   // std::stoi

bool Alpaca::Client::is_hedging() {
  return this->flags["hedge"].empty() ? false
                                      : (bool)std::stoi(this->flags["hedge"]);
}

#endif
