#include "lib/transmission/transmission.cpp" // Transmission
#include <iostream>
#include <map> // std::map

int main() {
  Transmission t;

  std::cout << "D counts: " << (t.shift_count(Transmission::gear_t::D))
            << std::endl;
  std::cout << "N counts: " << (t.shift_count(Transmission::gear_t::N))
            << std::endl;
  std::cout << "R counts: " << (t.shift_count(Transmission::gear_t::R))
            << std::endl;

  if (!t.current_gear()) {
    std::cout << "nullptr is falsey" << std::endl;
  }

  if (t.current_gear()) {
    std::cout << *(t.current_gear()) << std::endl;
  }

  if (t.previous_gear()) {
    std::cout << "Previous Gear: " << *(t.previous_gear()) << std::endl;
  }
}
