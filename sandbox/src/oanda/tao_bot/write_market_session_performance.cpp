#ifndef OANDA__TAO_BOT_write_market_session_performance
#define OANDA__TAO_BOT_write_market_session_performance

#include "tao_bot.h" // Oanda::TaoBot,

void Oanda::TaoBot::write_market_session_performance() {
  if (this->api_client.config.trade_setup_ml_mode != "TRAIN") {
    return;
  }

  this->db_market_session_performance.upsert({
      .debug = this->api_client.config.debug_sql,
      .env = this->api_client.load_env().dump(),
      .market_session_id = this->market_session_performance.market_session_id,
      .max_drawdown_percent =
          this->market_session_performance.max_drawdown_percent,
      .profit_loss_percent =
          this->market_session_performance.profit_loss_percent,
      .time_to_max_drawdown_seconds =
          this->market_session_performance.time_to_max_drawdown_seconds,
      .trade_setup_id = this->market_session_performance.trade_setup_id,
  });
}

#endif
