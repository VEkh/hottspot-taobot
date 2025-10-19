#ifndef OANDA__TAO_BOT_build_day_candle
#define OANDA__TAO_BOT_build_day_candle

#include "tao_bot.h"                   // Oanda::TaoBot, candle_t
#include "update_aggregate_candle.cpp" // update_aggregate_candle

void Oanda::TaoBot::build_day_candle() {
  for (const candle_t candle : this->latest_candles) {
    if (candle.closed_at > this->current_epoch) {
      break;
    }

    update_aggregate_candle(this->day_candle, candle);

    if (!this->api_client.config.trade_setup_ml_mode.empty() &&
        candle.closed_at <= this->market_session.warm_up_closed_at) {
      update_aggregate_candle(this->warm_up_candle, candle);
    }
  }

  if (!this->api_client.config.trade_setup_ml_mode.empty()) {
    this->market_session.close = this->day_candle.close;
    this->market_session.high = this->day_candle.high;
    this->market_session.low = this->day_candle.low;
    this->market_session.open = this->day_candle.open;
    this->market_session.warm_up_close = this->warm_up_candle.close;
    this->market_session.warm_up_high = this->warm_up_candle.high;
    this->market_session.warm_up_low = this->warm_up_candle.low;
    this->market_session.warm_up_open = this->warm_up_candle.open;
  }
}

#endif
