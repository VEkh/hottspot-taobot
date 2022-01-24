#ifndef OANDA__CLIENT_is_live
#define OANDA__CLIENT_is_live

#include "client.h" // Oanda::Client
#include <string>   // std::stoi

bool Oanda::Client::is_live() {
  return this->flags["paper"].empty() ? true
                                      : !((bool)std::stoi(flags["paper"]));
}

#endif
