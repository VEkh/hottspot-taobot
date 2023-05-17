#ifndef ALPACA__TAO_BOT_target_account_profit_ratio
#define ALPACA__TAO_BOT_target_account_profit_ratio

#include "tao_bot.h" // Alpaca::TaoBot
#include <map>       // std::map
#include <string>    // std::string

double Alpaca::TaoBot::target_account_profit_ratio() {
  const double ratio =
      this->TARGET_ACCOUNT_PROFIT_RATIOS[this->api_client.config.api_key];

  return ratio ? ratio : this->TARGET_ACCOUNT_PROFIT_RATIOS["live-alpha"];
}

#endif
