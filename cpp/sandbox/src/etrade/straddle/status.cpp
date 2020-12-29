#if !defined ETRADE__STRADDLE_status
#define ETRADE__STRADDLE_status

#include "straddle.h" // ETrade::Straddle, status_t

ETrade::Straddle::status_t ETrade::Straddle::status() {
  if (!buy_open_order.id && !sell_short_open_order.id) {
    return status_t::PENDING;
  }

  return status_t::OPEN;
}

#endif
