#ifndef OANDA__TAO_BOT_base_quantity
#define OANDA__TAO_BOT_base_quantity

#include "max_affordable_quantity.cpp" // max_affordable_quantity
#include "tao_bot.h"                   // Oanda::TaoBot
#include <algorithm>                   // std::max
#include <math.h>                      // floor, pow

int Oanda::TaoBot::base_quantity() {
  const int base_quantity_ = floor(max_affordable_quantity() /
                                   pow(2, this->MAX_EXPECTED_LOSS_STREAK + 1));

  return std::max(base_quantity_, 1);
}

#endif
