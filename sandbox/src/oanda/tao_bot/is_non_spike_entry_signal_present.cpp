// TODO: Decide
#ifndef OANDA__TAO_BOT_is_non_spike_entry_signal_present
#define OANDA__TAO_BOT_is_non_spike_entry_signal_present

#include "current_mid.cpp"                  // current_mid
#include "day_range_percentile.cpp"         // day_range_percentile
#include "is_trending.cpp"                  // is_trending
#include "latest_record_as_reversal.cpp"    // latest_record_as_reversal
#include "latest_record_reversal_after.cpp" // latest_record_reversal_after
#include "tao_bot.h" // Oanda::TaoBot, position_t, reversal_t, reversal_type_t

bool Oanda::TaoBot::is_non_spike_entry_signal_present() {
  const bool is_trending_ = is_trending();

  reversal_t entry_reversal_;

  const reversal_t record_high =
      latest_record_as_reversal(reversal_type_t::REVERSAL_HIGH);

  const reversal_t record_low =
      latest_record_as_reversal(reversal_type_t::REVERSAL_LOW);

  if (!is_trending_ && !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    const reversal_type_t type =
        last_position.open_order.action == order_action_t::BUY
            ? reversal_type_t::REVERSAL_HIGH
            : reversal_type_t::REVERSAL_LOW;

    entry_reversal_ = latest_record_as_reversal(type);
  }

  if (is_trending_) {
    reversal_t reversal;

    bool did_last_position_stop_profit = false;

    if (!this->closed_positions.empty()) {
      const position_t last_position = this->closed_positions.back();

      did_last_position_stop_profit =
          (bool)last_position.close_order.stop_profit_reversal.at;
    }

    if (did_last_position_stop_profit) {
      const position_t last_position = this->closed_positions.back();

      reversal = last_position.close_order.stop_profit_reversal;
    } else {
      reversal_t latest_high =
          latest_reversal_after(this->reversals, this->current_trend.at,
                                reversal_type_t::REVERSAL_HIGH);

      reversal_t latest_low =
          latest_reversal_after(this->reversals, this->current_trend.at,
                                reversal_type_t::REVERSAL_LOW);

      // TODO: Decide
      if (this->api_client.config.should_only_enter_at_record) {
        latest_high = latest_record_reversal_after(
            this->reversals, this->current_trend.at,
            reversal_type_t::REVERSAL_HIGH);

        latest_low = latest_record_reversal_after(
            this->reversals, this->current_trend.at,
            reversal_type_t::REVERSAL_LOW);
      }

      const double current_mid_ = current_mid();

      // TODO: Decide
      if (this->api_client.config.should_enter_in_trend_direction) {
        if (this->api_client.config.should_await_record_break) {
          if (current_mid_ >= record_high.mid) {
            latest_high = reversal_t();
            latest_low = record_low;
          } else if (current_mid_ <= record_low.mid) {
            latest_high = record_high;
            latest_low = reversal_t();
          } else {
            latest_high = reversal_t();
            latest_low = reversal_t();
          }
        } else {
          const double current_percentile =
              day_range_percentile(this->day_candle, current_mid_);

          if (current_percentile >= this->EQUATOR_PERCENTILE) {
            latest_high = reversal_t();
            latest_low = record_low;
          } else {
            latest_high = record_high;
            latest_low = reversal_t();
          }
        }
      }

      if (latest_high.mid &&
          day_range_percentile(this->day_candle, latest_high.mid) >=
              this->EQUATOR_PERCENTILE &&
          current_mid_ <= latest_high.mid) {
        reversal = latest_high;
      } else if (latest_low.mid &&
                 day_range_percentile(this->day_candle, latest_low.mid) <=
                     this->EQUATOR_PERCENTILE &&
                 current_mid_ >= latest_low.mid) {
        reversal = latest_low;
      }

      // TODO: Decide
      // const int reversal_at_minute = reversal.at / 60;
      // const int trend_at_minute = this->current_trend.at / 60;

      // if (reversal_at_minute < trend_at_minute) {
      //   reversal = reversal_t();
      // }

      // TODO: Decide
      if (!this->api_client.config.should_only_win_once &&
          this->has_stopped_profit) {
        const order_t last_close_order =
            this->closed_positions.back().close_order;

        if (record_high.at < last_close_order.timestamp &&
            record_low.at < last_close_order.timestamp) {
          reversal = reversal_t();
        }
        // TODO: Decide
      } else if (this->api_client.config.warm_up_period_hours) {
        const int current_epoch_minute = this->current_epoch / 60;
        const int trend_at_minute = this->current_trend.at / 60;

        if (current_epoch_minute < trend_at_minute) {
          reversal = reversal_t();
        }
      } else {
        const int reversal_at_minute = reversal.at / 60;
        const int trend_at_minute = this->current_trend.at / 60;

        if (reversal_at_minute < trend_at_minute) {
          reversal = reversal_t();
        }
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
