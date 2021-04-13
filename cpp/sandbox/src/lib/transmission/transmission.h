#if !defined TRANSMISSION_h
#define TRANSMISSION_h

#include "lib/formatted.cpp" // Formatted
#include <map>               // std::vector
#include <vector>            // std::vector

class Transmission {
public:
  enum gear_t {
    D = 1,
    N = 0,
    R = -1,
  };

  Formatted::fmt_stream_t fmt = Formatted::stream();
  std::vector<gear_t> gear_shifts;

  Transmission(){};

  gear_t *current_gear();
  gear_t *previous_gear();
  int shift_count(const gear_t);
  void log();
  void shift_gear(const gear_t gear) { gear_shifts.push_back(gear); };
};

#endif
