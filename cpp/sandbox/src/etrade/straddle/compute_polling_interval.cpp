#if !defined ETRADE__STRADDLE_compute_polling_interval
#define ETRADE__STRADDLE_watch

#include "status.cpp" // status
#include "straddle.h" // ETrade::Straddle, status_t

double ETrade::Straddle::compute_polling_interval() {
  if (status() == status_t::PENDING) {
    return 20;
  }

  return 0.5;
}

#endif
