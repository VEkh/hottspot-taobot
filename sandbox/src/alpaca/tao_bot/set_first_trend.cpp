// TODO: Decide
#ifndef ALPACA__TAO_BOT_set_first_trend
#define ALPACA__TAO_BOT_set_first_trend

#include "set_first_trend.cpp"        // set_first_trend
#include "is_trending.cpp"            // is_trending
#include "latest_record_reversal.cpp" // latest_record_reversal
#include "tao_bot.h" // Alpaca::TaoBot, reversal_t, reversal_type_t, trend_t

void Alpaca::TaoBot::set_first_trend() {
  if (!this->api_client.config.should_await_first_trend) {
    return;
  }

  if (!this->closed_positions.empty()) {
    return;
  }

  if (is_trending()) {
    return;
  }

  if (this->reversals.any_empty()) {
    return;
  }

  // TODO: Decide how / when to set trend
  const reversal_t record_reversal = latest_record_reversal(this->reversals);

  this->current_trend = {
      .at = this->current_epoch,
      .trend = record_reversal.type == reversal_type_t::REVERSAL_HIGH
                   ? trend_t::TREND_UP
                   : trend_t::TREND_DOWN,
  };
}

#endif
