#if !defined TRANSMISSION_previous_gear
#define TRANSMISSION_previous_gear

#include "transmission.h" // Transmission, gear_t

Transmission::gear_t *Transmission::previous_gear() {
  if (this->gear_shifts.size() < 2) {
    return nullptr;
  }

  return &(this->gear_shifts.at(this->gear_shifts.size() - 2));
}

#endif
