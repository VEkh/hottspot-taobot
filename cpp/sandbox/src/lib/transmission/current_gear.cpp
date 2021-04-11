#if !defined TRANSMISSION_current_gear
#define TRANSMISSION_current_gear

#include "transmission.h" // Transmission, gear_t

Transmission::gear_t *Transmission::current_gear() {
  if (this->gear_shifts.empty()) {
    return nullptr;
  }

  return &(this->gear_shifts.back());
}

#endif
