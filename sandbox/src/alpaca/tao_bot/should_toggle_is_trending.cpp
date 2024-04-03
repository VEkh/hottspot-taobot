#ifndef ALPACA__TAO_BOT_should_toggle_is_trending
#define ALPACA__TAO_BOT_should_toggle_is_trending

#include "is_trend_indicating_loss.cpp" // is_trend_indicating_loss
#include "is_trending.cpp"              // is_trending
#include "tao_bot.h"                    // Alpaca::TaoBot, position_t

bool Alpaca::TaoBot::should_toggle_is_trending() {
  if (!this->open_order_ptr) {
    return false;
  }

  if (is_trending()) {
    return true;
  }

  const int toggle_n = this->api_client.config.toggle_is_trending_after_n;

  if (!toggle_n) {
    return false;
  }

  const bool is_valid_loss_streak =
      (this->performance.trend_loss_count + 1) % toggle_n == 0;

  if (!is_valid_loss_streak) {
    return false;
  }

  return is_trend_indicating_loss({
      .close_order = this->close_order,
      .open_order = this->open_order,
  });
}

#endif
