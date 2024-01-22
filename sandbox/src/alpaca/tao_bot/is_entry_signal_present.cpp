// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "current_mid.cpp" // current_mid
#include "tao_bot.h"       // Alpaca::TaoBot, range_t

#include "is_consolidating.cpp"  // is_consolidating
#include "is_reversing_loss.cpp" // is_reversing_loss

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator) {
    return false;
  }

  if (!this->api_client.config.should_await_consolidation_indicator) {
    return false;
  }

  if (!is_consolidating()) {
    return false;
  }

  if (!this->reversals.highs.empty() || !this->reversals.lows.empty()) {
    return true;
  }

  return false;
}

// #include "is_breaking_consolidation.cpp"  // is_breaking_consolidation
// #include "is_near_consolidation_edge.cpp" // is_near_consolidation_edge
// #include "is_reversing_loss.cpp"          // is_reversing_loss

// bool Alpaca::TaoBot::is_entry_signal_present() {
//   if (!this->api_client.config.should_await_consolidation_indicator) {
//     return false;
//   }

//   // TODO: Decide
//   if (is_reversing_loss()) {
//     return true;
//   }

//   for (int duration : this->consolidation_durations) {
//     if (is_consolidating(duration) && is_near_consolidation_edge(duration)) {
//       return true;
//     }

//     if (is_breaking_consolidation(duration)) {
//       return true;
//     }
//   }

//   return false;
// }

#endif
