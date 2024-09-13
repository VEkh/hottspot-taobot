#ifndef MARKET_AVAILABILITY__BASE_list_to_lookup
#define MARKET_AVAILABILITY__BASE_list_to_lookup

#include "base.h" // MarketAvailability::Base
#include <list>   // std::list
#include <map>    // std::map

template <typename KeyType>
std::map<KeyType, bool>
MarketAvailability::Base::list_to_lookup(const std::list<KeyType> in) {
  std::map<KeyType, bool> out;

  for (const KeyType key : in) {
    out[key] = true;
  }

  return out;
}

#endif
