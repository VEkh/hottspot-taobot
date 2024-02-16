// TODO: Decide
#ifndef ALPACA__TAO_BOT_should_toggle_is_trending
#define ALPACA__TAO_BOT_should_toggle_is_trending

#include "tao_bot.h" // Alpaca::TaoBot, position_t

bool Alpaca::TaoBot::should_toggle_is_trending() {
  if (!this->open_order_ptr) {
    return false;
  }

  const int toggle_n = this->api_client.config.toggle_is_trending_after_n;

  if (!toggle_n) {
    return false;
  }

  const bool is_valid_loss_streak =
      (this->performance.loss_streaks.current + 1) % toggle_n == 0;

  if (!is_valid_loss_streak) {
    return false;
  }

  if (this->is_trending) {
    return true;
  }

  const double static_one_sec_variance = this->avg_one_sec_variances.running;

  const bool was_last_gain_small =
      this->open_order_ptr->max_profit < 10 * static_one_sec_variance;

  return was_last_gain_small;
}

#endif
