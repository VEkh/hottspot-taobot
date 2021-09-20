#ifndef ETRADE__TAO_BOT_secured_profit_ratio
#define ETRADE__TAO_BOT_secured_profit_ratio

/*
 * ETrade::TaoBot
 */
#include "tao_bot.h"

#include <math.h> // exp

double ETrade::TaoBot::secured_profit_ratio() {
  const double min = 0.8;
  const double max = 0.9;

  if (!this->exit_prices.min_profit) {
    return min;
  }

  const double x = this->open_order.profit / this->exit_prices.min_profit;
  const double y_shift = min;
  const double y_coefficient = max - min;
  const double x_shift = 1.5;
  const double x_coefficient = 6;

  return (y_coefficient / (1 + exp(-x_coefficient * (x - x_shift)))) + y_shift;
}

#endif
