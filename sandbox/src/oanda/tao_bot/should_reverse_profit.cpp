// TODO: Decide
#ifndef OANDA__TAO_BOT_should_reverse_profit
#define OANDA__TAO_BOT_should_reverse_profit

#include "first_reversal_after.cpp"         // first_reversal_after
#include "is_trend_slipping.cpp"            // is_trend_slipping
#include "latest_record_as_reversal.cpp"    // latest_record_as_reversal
#include "latest_record_reversal_after.cpp" // latest_record_reversal_after
#include "latest_reversal_after.cpp"        // latest_reversal_after
#include "tao_bot.h"                        // Oanda::TaoBot, reversal_t
#include <string>                           // std::string

bool Oanda::TaoBot::should_reverse_profit() {
  if (this->api_client.config.should_enter_at_spike) {
    return false;
  }

  if (!this->api_client.config.should_always_reverse_profit &&
      this->closed_positions.empty()) {
    return false;
  }

  reversal_t stop_profit_reversal = latest_record_reversal_after(
      this->reversals, this->open_order_ptr->timestamp,
      this->open_order_ptr->entry_reversal.opposite_type());

  // TODO: Decide
  const double post_win_reverse_profit_percentile =
      this->api_client.config.post_win_reverse_profit_percentile;
  double trend_slipping_percentile = this->EQUATOR_PERCENTILE;

  if (!this->api_client.config.should_only_win_once &&
      this->has_stopped_profit && post_win_reverse_profit_percentile) {
    trend_slipping_percentile = post_win_reverse_profit_percentile;
  }

  if (stop_profit_reversal.at &&
      is_trend_slipping(this->open_order_ptr, trend_slipping_percentile)) {
    // TODO: Decide
    if (this->api_client.config.should_reverse_loss_at_equator) {
      stop_profit_reversal.is_reversible =
          trend_slipping_percentile == this->EQUATOR_PERCENTILE;

      stop_profit_reversal.is_record_only_reversible =
          !stop_profit_reversal.is_reversible;
    }

    this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

    return true;
  }

  return false;
}

// // Wrong, but more profitable (?)
// bool Oanda::TaoBot::should_reverse_profit() {
//   if (this->api_client.config.should_enter_at_spike) {
//     return false;
//   }

//   if (!this->api_client.config.should_always_reverse_profit &&
//       this->closed_positions.empty()) {
//     return false;
//   }

//   reversal_t stop_profit_reversal = latest_reversal_after(
//       this->reversals, this->open_order_ptr->timestamp,
//       this->open_order_ptr->entry_reversal.opposite_type());

//   if (stop_profit_reversal.at) {
//     const reversal_t record_reversal =
//         latest_record_as_reversal(stop_profit_reversal.type);

//     stop_profit_reversal =
//         first_reversal_after(this->reversals,
//         this->open_order_ptr->timestamp,
//                              stop_profit_reversal.type, record_reversal.mid);

//     if (record_reversal.mid == stop_profit_reversal.mid &&
//         is_trend_slipping(this->open_order_ptr, this->EQUATOR_PERCENTILE)) {
//       this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

//       return true;
//     }
//   }

//   return false;
// }

#endif
