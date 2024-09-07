#ifndef ALPACA__TAO_BOT_is_entry_signal_present
#define ALPACA__TAO_BOT_is_entry_signal_present

#include "day_range_percentile.cpp"   // day_range_percentile
#include "first_reversal_after.cpp"   // first_reversal_after
#include "is_trending.cpp"            // is_trending
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h" // Alpaca::TaoBot, position_t, reversal_t, reversal_type_t

#include <time.h> // tm

bool Alpaca::TaoBot::is_entry_signal_present() {
  const bool is_trending_ = is_trending();

  reversal_t entry_reversal_ = latest_record_reversal();

  if (!is_trending_ && !this->closed_positions.empty()) {
    const position_t last_position = this->closed_positions.back();

    const reversal_type_t type =
        last_position.open_order.action == order_action_t::BUY
            ? reversal_type_t::REVERSAL_HIGH
            : reversal_type_t::REVERSAL_LOW;

    entry_reversal_ = latest_record_reversal(type);
  }

  if (is_trending_ && this->reversals.timeframe_minutes) {
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
      const reversal_t first_high =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_HIGH);

      const reversal_t first_low =
          first_reversal_after(this->reversals, this->current_trend.at,
                               reversal_type_t::REVERSAL_LOW);

      if (first_high.mid &&
          day_range_percentile(first_high.mid) >= this->EQUATOR_PERCENTILE) {
        reversal = first_high;
      } else if (first_low.mid && day_range_percentile(first_low.mid) <=
                                      this->EQUATOR_PERCENTILE) {
        reversal = first_low;
      }

      const int reversal_at_minute = reversal.at / 60;
      const int trend_at_minute = this->current_trend.at / 60;

      if (reversal_at_minute < trend_at_minute) {
        reversal = reversal_t();
      }
    }

    entry_reversal_ = reversal;
  }

  // TODO: Decide
  if (this->api_client.config.should_market_open_trend_start &&
      this->closed_positions.empty()) {
    const int market_open_trend_duration =
        this->reversals.timeframe_minutes / 2;

    tm market_open_tm = ::utils::time_::epoch_to_tm(
        this->market_availability.market_open_epoch, "America/Chicago");

    tm trend_at = {
        .tm_sec = 0,
        .tm_min = market_open_tm.tm_min + market_open_trend_duration,
        .tm_hour = market_open_tm.tm_hour,
    };

    if (::utils::time_::is_at_least(this->current_epoch, trend_at,
                                    "America/Chicago")) {
      const long int trend_at_epoch =
          this->market_availability.market_open_epoch +
          market_open_trend_duration;

      const reversal_type_t reversal_type =
          current_mid() >= this->day_candle.open
              ? reversal_type_t::REVERSAL_LOW
              : reversal_type_t::REVERSAL_HIGH;

      const double reversal_mid = reversal_type == reversal_type_t::REVERSAL_LOW
                                      ? this->day_candle.low
                                      : this->day_candle.high;

      this->current_trend.trend = trend_t::TREND_CONSOLIDATION;

      entry_reversal_ = reversal_t({
          .at = (double)trend_at_epoch,
          .mid = reversal_mid,
          .type = reversal_type,

      });
    }
  }

  if (entry_reversal_.at) {
    this->entry_reversal = entry_reversal_;

    return true;
  }

  return false;
}

#endif
