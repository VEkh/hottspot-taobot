#ifndef ETRADE__TAO_BOT_should_terminate
#define ETRADE__TAO_BOT_should_terminate

#include "tao_bot.h" // ETrade::TaoBot, order_status_t

bool ETrade::TaoBot::should_terminate() {
  if (!::utils::time_::is_end_of_day()) {
    return false;
  }

  if (!this->close_order_ptr) {
    return true;
  }

  return this->close_order_ptr &&
         this->close_order.status == order_status_t::ORDER_EXECUTED;
}

#endif
