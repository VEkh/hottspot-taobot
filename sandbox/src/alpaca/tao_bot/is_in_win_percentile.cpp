// TODO: Decide
#ifndef ALPACA__TAO_BOT_is_in_win_percentile
#define ALPACA__TAO_BOT_is_in_win_percentile

#include "day_range_percentile.cpp"      // day_range_percentile
#include "position_range_percentile.cpp" // day_range_percentile // TODO: Decide
#include "tao_bot.h" // Alpaca::TaoBot, order_action_t, order_t
#include <string>    // std::string

bool Alpaca::TaoBot::is_in_win_percentile(const order_t *order,
                                          const double profit) {
  if (!this->win_percentile) {
    return false;
  }

  if (!order) {
    return false;
  }

  if (profit < 0) {
    return false;
  }

  const double win_percentile = this->win_percentile;

  const std::string win_percentile_range =
      this->api_client.config.win_percentile_range;

  double profit_percentile;

  if (win_percentile_range == "DAY") {
    profit_percentile = day_range_percentile(order, profit);
  } else if (win_percentile_range == "POSITION") {
    profit_percentile = position_range_percentile(order, profit);
  }

  return profit_percentile >= win_percentile;
}

#endif
