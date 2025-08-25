#ifndef OANDA__TAO_BOT_write_market_session_performance
#define OANDA__TAO_BOT_write_market_session_performance

#include "tao_bot.h" // Oanda::TaoBot,

void Oanda::TaoBot::write_market_session_performance() {
  if (this->api_client.config.trade_setup_ml_mode != "TRAIN") {
    return;
  }

  const double initial_equity = this->account_snapshot.original_equity;
  const double current_equity = this->account_snapshot.equity;
  const double profit_loss_percent =
      ((current_equity - initial_equity) / initial_equity) * 100.0;

  this->db_market_session_performance.upsert({
      .debug = this->api_client.config.debug_sql,
      .env = this->api_client.load_env().dump(),
      .market_session_id = this->market_session.id,
      .profit_loss_percent = profit_loss_percent,
      .trade_setup_id = this->trade_setup.id,
  });
}

#endif
