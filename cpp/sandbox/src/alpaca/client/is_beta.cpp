#ifndef ALPACA__CLIENT_is_beta
#define ALPACA__CLIENT_is_beta

#include "client.h" // Alpaca::Client
#include <string>   // std::stoi

bool Alpaca::Client::is_beta() {
  return this->flags["beta"].empty() ? false
                                     : (bool)std::stoi(this->flags["beta"]);
}

#endif
