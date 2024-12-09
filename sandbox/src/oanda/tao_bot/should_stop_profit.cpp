// TODO: Decide
#ifndef OANDA__TAO_BOT_should_stop_profit
#define OANDA__TAO_BOT_should_stop_profit

#include "latest_reversal_after.cpp" // latest_reversal_after
#include "tao_bot.h"                 // Oanda::TaoBot, reversal_t

// TODO: Decide
#include "is_reversal_after.cpp" // is_reversal_after
#include "is_trend_slipping.cpp" // is_trend_slipping

bool Oanda::TaoBot::should_stop_profit() {
  if (!this->api_client.config.should_stop_profit) {
    return false;
  }

  if (!this->open_order_ptr) {
    return false;
  }

  const stop_profit_type_t stop_profit_type =
      this->open_order_ptr->stop_profit_type;

  if (stop_profit_type != stop_profit_type_t::STOP_PROFIT_EXTEND_RANGE &&
      stop_profit_type != stop_profit_type_t::STOP_PROFIT_CROSS_RANGE) {
    return false;
  }

  if (this->exit_prices.stop_profit &&
      this->open_order_ptr->max_profit < this->exit_prices.stop_profit) {
    return false;
  }

  if (!is_trend_slipping(this->open_order_ptr)) {
    return false;
  }

  this->slow_reverse_loss_count = 0; // TODO: Decide

  return true;
}

// bool Oanda::TaoBot::should_stop_profit() {
//   if (!this->api_client.config.should_stop_profit) {
//     return false;
//   }

//   if (!this->open_order_ptr) {
//     return false;
//   }

//   if (this->open_order_ptr->stop_profit_type !=
//       stop_profit_type_t::STOP_PROFIT_RETURN_TO_PEAK) {
//     return false;
//   }

//   if (!this->api_client.config.stop_profit_ratio) {
//     return false;
//   }

//   double ref_epoch = this->open_order_ptr->max_profit_at;
//   reversal_t entry_reversal_ = this->open_order_ptr->entry_reversal;

//   reversals_t stop_profit_reversals =
//       this->secondary_reversals.timeframe_minutes ? this->secondary_reversals
//                                                   : this->reversals;

//   const reversal_t stop_profit_reversal = latest_reversal_after(
//       stop_profit_reversals, ref_epoch, entry_reversal_.opposite_type());

//   if (!stop_profit_reversal.at) {
//     return false;
//   }

//   const double current_profit = this->open_order_ptr->profit;
//   const double execution_mid = this->open_order_ptr->execution_price;
//   const double max_profit = this->open_order_ptr->max_profit;

//   const double stop_profit_reversal_profit =
//       stop_profit_reversal.type == reversal_type_t::REVERSAL_HIGH
//           ? stop_profit_reversal.mid - execution_mid
//           : execution_mid - stop_profit_reversal.mid;

//   const double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

//   if (stop_profit_reversal_profit > 0 &&
//       current_profit >= stop_profit_ratio * stop_profit_reversal_profit) {
//     return true;
//   }

//   if (max_profit > 0 && current_profit >= stop_profit_ratio * max_profit) {
//     return true;
//   }

//   return false;
// }
// bool Oanda::TaoBot::should_stop_profit() {
//   if (!this->api_client.config.should_stop_profit) {
//     return false;
//   }

//   if (!this->open_order_ptr) {
//     return false;
//   }

//   if (this->open_order_ptr->stop_profit_type !=
//       stop_profit_type_t::STOP_PROFIT_RETURN_TO_PEAK) {
//     return false;
//   }

//   const double current_profit = this->open_order_ptr->profit;

//   if (this->exit_prices.stop_profit) {
//     return current_profit >= this->exit_prices.stop_profit;
//   }

//   // reversal_t stop_profit_reversal = first_reversal_after(
//   //     this->reversals, this->open_order_ptr->timestamp,
//   //     this->open_order_ptr->entry_reversal.opposite_type());

//   // if (!stop_profit_reversal.at) {
//   //   return false;
//   // }

//   // if (!stop_profit_reversal.is_record) {
//   //   return false;
//   // }

//   // if (is_trend_slipping(this->open_order_ptr)) {
//   //   return true;
//   // }

//   // return false;

//   if (!this->api_client.config.stop_profit_ratio) {
//     return false;
//   }

//   reversal_t entry_reversal_ = this->open_order_ptr->entry_reversal;
//   double ref_epoch = this->open_order_ptr->timestamp;

//   if (this->open_order_ptr->entry_reversal.is_record_only_reversible) {
//     const reversal_t stop_profit_reversal =
//         latest_record_reversal(entry_reversal_.opposite_type());

//     if (!is_reversal_after(stop_profit_reversal, ref_epoch)) {
//       return false;
//     } else {
//       ref_epoch = stop_profit_reversal.at;
//     }
//   }

//   reversals_t stop_profit_reversals =
//       this->secondary_reversals.timeframe_minutes ? this->secondary_reversals
//                                                   : this->reversals;

//   const reversal_t stop_profit_reversal = latest_reversal_after(
//       stop_profit_reversals, ref_epoch, entry_reversal_.opposite_type());

//   if (!stop_profit_reversal.at) {
//     return false;
//   }

//   const double execution_mid = this->open_order_ptr->execution_price;
//   const double max_profit = this->open_order_ptr->max_profit;

//   const double stop_profit_reversal_profit =
//       stop_profit_reversal.type == reversal_type_t::REVERSAL_HIGH
//           ? stop_profit_reversal.mid - execution_mid
//           : execution_mid - stop_profit_reversal.mid;

//   const double stop_profit_ratio = this->api_client.config.stop_profit_ratio;

//   if (stop_profit_reversal_profit > 0 &&
//       current_profit >= stop_profit_ratio * stop_profit_reversal_profit) {
//     return true;
//   }

//   if (max_profit > 0 && current_profit >= stop_profit_ratio * max_profit) {
//     return true;
//   }

//   return false;
// }

#endif
