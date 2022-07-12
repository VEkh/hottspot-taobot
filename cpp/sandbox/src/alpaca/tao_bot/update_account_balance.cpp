#ifndef ALPACA__TAO_BOT_update_account_balance
#define ALPACA__TAO_BOT_update_account_balance

#include "get_account_balance.cpp" // get_account_balance
#include "tao_bot.h"               // Alpaca::TaoBot
#include <ctime>                   // std::time

void Alpaca::TaoBot::update_account_balance() {
  this->account_balance =
      get_account_balance(this->api_client, this->account_balance);
}

#endif
