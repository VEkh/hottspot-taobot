#ifndef OANDA__TAO_BOT_update_market_session_performance
#define OANDA__TAO_BOT_update_market_session_performance

#include "tao_bot.h" // Oanda::TaoBot
#include <algorithm> // std::max, std::min

void Oanda::TaoBot::update_market_session_performance() {
  if (this->api_client.config.trade_setup_ml_mode.empty()) {
    return;
  }

  const double current_equity = this->account_snapshot.equity;
  const double max_equity = this->account_snapshot.max_equity;
  const double max_equity_at = this->account_snapshot.max_equity_timestamp;

  const double original_equity = this->account_snapshot.original_equity;

  const double profit_loss_percent =
      ((current_equity - original_equity) / original_equity) * 100.0;

  double drawdown_percent = 0.0;
  double max_drawdown_percent =
      this->market_session_performance.max_drawdown_percent;

  double time_to_max_drawdown_seconds =
      this->market_session_performance.time_to_max_drawdown_seconds;

  if (max_equity) {
    drawdown_percent = ((current_equity - max_equity) / max_equity) * 100.0;
    drawdown_percent = std::min(drawdown_percent, 0.0);
    max_drawdown_percent = std::min(drawdown_percent, max_drawdown_percent);
  }

  if (max_drawdown_percent == drawdown_percent) {
    time_to_max_drawdown_seconds = this->current_epoch - max_equity_at;
  }

  this->market_session_performance = {
      .drawdown_percent = drawdown_percent,
      .market_session_id = this->market_session.id,
      .max_drawdown_percent = max_drawdown_percent,
      .max_equity = max_equity,
      .max_equity_at = max_equity_at,
      .profit_loss_percent = profit_loss_percent,
      .time_to_max_drawdown_seconds = time_to_max_drawdown_seconds,
      .trade_setup_id = this->trade_setup.id,
  };
}

#endif
