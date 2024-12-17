// TODO: Decide
#ifndef OANDA__TAO_BOT_should_reverse_profit
#define OANDA__TAO_BOT_should_reverse_profit

#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trend_slipping.cpp"      // is_trend_slipping
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "latest_reversal_after.cpp"  // latest_reversal_after
#include "tao_bot.h"                  // Oanda::TaoBot, reversal_t
#include <string>                     // std::string

// bool Oanda::TaoBot::should_reverse_profit() {
//   if (this->closed_positions.empty()) {
//     return false;
//   }

//   // TODO: Decide
//   if (this->api_client.config.should_stop_profit &&
//       !this->api_client.config.should_reverse_profit) {
//     return false;
//   }

//   reversal_t stop_profit_reversal = latest_reversal_after(
//       this->reversals, this->open_order_ptr->timestamp,
//       this->open_order_ptr->entry_reversal.opposite_type());

//   if (stop_profit_reversal.at) {
//     const reversal_t record_reversal =
//         latest_record_reversal(stop_profit_reversal.type);

//     stop_profit_reversal =
//         first_reversal_after(this->reversals,
//         this->open_order_ptr->timestamp,
//                              stop_profit_reversal.type, true);

//     if (record_reversal.mid == stop_profit_reversal.mid &&
//         is_trend_slipping(this->open_order_ptr)) {
//       this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;

//       return true;
//     }
//   }

//   return false;
// }

// #include "is_trending.cpp" // is_trending

// // TODO: Decide
// bool Oanda::TaoBot::should_reverse_profit() {
//   if (this->api_client.config.should_stop_profit &&
//       !this->api_client.config.should_reverse_profit) {
//     return false;
//   }

//   if (is_trending()) {
//     return false;
//   }

//   reversal_t stop_profit_reversal = latest_reversal_after(
//       this->secondary_reversals, this->open_order_ptr->timestamp,
//       this->open_order_ptr->entry_reversal.opposite_type());

//   if (!stop_profit_reversal.at) {
//     return false;
//   }

//   if (!stop_profit_reversal.is_record) {
//     return false;
//   }

//   if (this->open_order_ptr->profit < 0 &&
//       this->api_client.config.should_only_reverse_loss) {
//     this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;
//   }

//   if (this->open_order_ptr->profit >= 0 &&
//       !this->api_client.config.should_only_reverse_loss) {
//     this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;
//   }

//   return true;
// }

// TODO: Decide
#include "is_reversal_after.cpp" // is_reversal_after

bool Oanda::TaoBot::should_reverse_profit() {
  if (!this->api_client.config.should_reverse_profit) {
    return false;
  }

  if (this->open_order_ptr->stop_profit_type !=
      stop_profit_type_t::STOP_PROFIT_CROSS_RANGE) {
    return false;
  }

  const double ref_epoch = this->open_order_ptr->timestamp;

  reversal_t stop_profit_reversal;

  // TODO: Decide
  // if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
  stop_profit_reversal = latest_record_reversal(
      this->open_order_ptr->entry_reversal.opposite_type());

  if (!is_reversal_after(stop_profit_reversal, ref_epoch)) {
    stop_profit_reversal = reversal_t();
  }
  // } else {
  //   stop_profit_reversal = latest_reversal_after(
  //       this->secondary_reversals, ref_epoch,
  //       this->open_order_ptr->entry_reversal.opposite_type());
  // }

  if (!stop_profit_reversal.at) {
    return false;
  }

  if (!is_trend_slipping(this->open_order_ptr)) {
    return false;
  }

  // if (this->open_order_ptr->profit < 0) {
  //   this->close_order_ptr->stop_profit_reversal = stop_profit_reversal;
  // }

  this->slow_reverse_loss_count = 0; // TODO: Decide
  return true;
}

#endif
