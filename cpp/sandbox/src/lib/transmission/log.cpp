#if !defined TRANSMISSION_log
#define TRANSMISSION_log

#include "current_gear.cpp" // current_gear
#include "shift_count.cpp"  // shift_count
#include "transmission.h"   // Transmission, fmt, gear_t
#include <iostream>         // std::cout, std::endl

void Transmission::log() {
  std::map<gear_t, const char *> gear_to_string = {
      {gear_t::D, "D"},
      {gear_t::N, "N"},
      {gear_t::R, "R"},
  };

  gear_t *current_gear_ptr = current_gear();

  std::cout << fmt.bold << fmt.magenta << fmt.underline;
  std::cout << "🚘 Transmission" << std::endl;
  std::cout << fmt.reset;

  std::cout << fmt.bold << fmt.magenta;

  std::cout << "Current Gear: "
            << (current_gear_ptr ? gear_to_string[*current_gear_ptr] : "P")
            << std::endl;

  std::cout << "D counts: " << (shift_count(Transmission::gear_t::D))
            << std::endl;
  std::cout << "N counts: " << (shift_count(Transmission::gear_t::N))
            << std::endl;
  std::cout << "R counts: " << (shift_count(Transmission::gear_t::R))
            << std::endl;

  std::cout << fmt.reset << std::endl;
}

#endif
