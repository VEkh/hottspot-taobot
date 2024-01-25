// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "is_breaking_consolidation.cpp" // is_breaking_consolidation
#include "is_consolidating.cpp"          // is_consolidating
#include "is_nearest_reversal_low.cpp"   // is_nearest_reversal_low
#include "is_reversing_loss.cpp"         // is_reversing_loss
#include "is_trend_reversing.cpp"        // is_trend_reversing
#include "is_trending.cpp"               // is_trending
#include "lib/utils/time.cpp"            // ::utils::time_
#include "relation_to_consolidation.cpp" // relation_to_consolidation
#include "tao_bot.h"                     // Alpaca::TaoBot, range_t

bool Alpaca::TaoBot::is_entry_signal_present() {
  if (!this->api_client.config.should_await_reversal_indicator &&
      !this->api_client.config.should_await_consolidation_indicator &&
      !this->api_client.config.should_await_trend_indicator) {
    return false;
  }

  if (this->api_client.config.should_await_trend_indicator) {
    if (is_trending()) {
      return true;
    }
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
