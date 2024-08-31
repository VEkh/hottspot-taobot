#ifndef FOREX_AVAILABILITY_list_to_lookup
#define FOREX_AVAILABILITY_list_to_lookup

#include "forex_availability.h" // ForexAvailability
#include <list>                 // std::list
#include <map>                  // std::map
#include <string>               // std::string

template <typename KeyType>
std::map<KeyType, bool>
ForexAvailability::list_to_lookup(const std::list<KeyType> in) {
  std::map<KeyType, bool> out;

  for (const KeyType key : in) {
    out[key] = true;
  }

  return out;
}

#endif
