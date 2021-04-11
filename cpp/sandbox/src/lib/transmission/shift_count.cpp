#if !defined TRANSMISSION_shift_count
#define TRANSMISSION_shift_count

#include "transmission.h" // Transmission, gear_shifts, gear_t
#include <map>            // std::map

int Transmission::shift_count(const gear_t gear) {
  std::map<gear_t, int> gear_shift_counts = {
      {gear_t::D, 0},
      {gear_t::N, 0},
      {gear_t::R, 0},
  };

  for (gear_t g : this->gear_shifts) {
    gear_shift_counts[g]++;
  }

  return gear_shift_counts[gear];
}

#endif
