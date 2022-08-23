#ifndef OANDA__TAO_BOT_update_account_balance
#define OANDA__TAO_BOT_update_account_balance

#include "get_account_balance.cpp" // get_account_balance
#include "tao_bot.h"               // Oanda::TaoBot
#include <ctime>                   // std::time

void Oanda::TaoBot::update_account_balance() {
  this->account_balance = get_account_balance(this->account_balance);
}

#endif
