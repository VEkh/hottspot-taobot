#ifndef ALPACA__TAO_BOT_target_account_profit_ratio
#define ALPACA__TAO_BOT_target_account_profit_ratio

#include "tao_bot.h" // Alpaca::TaoBot
#include <map>       // std::map
#include <string>    // std::string

double Alpaca::TaoBot::target_account_profit_ratio() {
  return this->api_client.config.account_stop_profit_ratio;
}

#endif
