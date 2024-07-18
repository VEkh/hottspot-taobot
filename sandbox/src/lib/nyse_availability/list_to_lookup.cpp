#ifndef NYSE_AVAILABILITY_list_to_lookup
#define NYSE_AVAILABILITY_list_to_lookup

#include "nyse_availability.h" // NyseAvailability
#include <list>                // std::list
#include <map>                 // std::map
#include <string>              // std::string

template <typename KeyType>
std::map<KeyType, bool>
NyseAvailability::list_to_lookup(const std::list<KeyType> in) {
  std::map<KeyType, bool> out;

  for (const KeyType key : in) {
    out[key] = true;
  }

  return out;
}

#endif
