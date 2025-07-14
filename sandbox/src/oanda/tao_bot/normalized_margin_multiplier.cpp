// TODO: Decide
#ifndef OANDA__TAO_BOT_normalized_margin_multiplier
#define OANDA__TAO_BOT_normalized_margin_multiplier

#include "margin_normalization_factor.cpp" // margin_normalization_factor
#include "tao_bot.h"                       // Oanda::TaoBot

double Oanda::TaoBot::normalized_margin_multiplier() {
  return this->api_client.config.margin_multiplier *
         margin_normalization_factor();
}

#endif
