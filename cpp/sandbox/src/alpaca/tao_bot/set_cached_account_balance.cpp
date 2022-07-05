#ifndef ALPACA__TAO_BOT_set_cached_account_balance
#define ALPACA__TAO_BOT_set_cached_account_balance

#include "fetch_account_balance.cpp" // fetch_account_balance
#include "tao_bot.h"                 // Alpaca::TaoBot
#include <ctime>                     // std::time

void Alpaca::TaoBot::set_cached_account_balance() {
  const int CACHE_EXPIRATION = 1 * 60;

  if ((std::time(nullptr) - this->account_balance.timestamp) <
      CACHE_EXPIRATION) {
    return;
  }

  this->account_balance =
      fetch_account_balance(this->api_client, this->account_balance);
}

#endif
