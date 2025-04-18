#ifndef ALPACA__TAO_BOT_is_record_break_entry_signal_present
#define ALPACA__TAO_BOT_is_record_break_entry_signal_present

#include "current_mid.cpp"                   // current_mid
#include "did_last_position_stop_profit.cpp" // did_last_position_stop_profit
#include "is_trending.cpp"                   // is_trending
#include "latest_record_as_reversal.cpp"     // latest_record_as_reversal
#include "should_nullify_entry_reversal.cpp" // should_nullify_entry_reversal
#include "tao_bot.h" // Alpaca::TaoBot, position_t, reversal_t, reversal_type_t

bool Alpaca::TaoBot::is_record_break_entry_signal_present() {
  const bool is_trending_ = is_trending();

  reversal_t entry_reversal_;

  const reversal_t record_high =
      latest_record_as_reversal(reversal_type_t::REVERSAL_HIGH);

  const reversal_t record_low =
      latest_record_as_reversal(reversal_type_t::REVERSAL_LOW);

  if (!is_trending_ && !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    entry_reversal_ = last_position.open_order.action == order_action_t::BUY
                          ? record_high
                          : record_low;
  }

  if (is_trending_) {
    reversal_t reversal;

    if (did_last_position_stop_profit()) {
      const position_t last_position = this->closed_positions.back();

      reversal = last_position.close_order.stop_profit_reversal;
    } else {
      const double current_mid_ = current_mid();

      if (current_mid_ >= record_high.mid) {
        reversal = record_low;
      } else if (current_mid_ <= record_low.mid) {
        reversal = record_high;
      }

      if (should_nullify_entry_reversal()) {
        reversal = reversal_t();
      }
    }

    entry_reversal_ = reversal;
  }

  if (entry_reversal_.at) {
    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
