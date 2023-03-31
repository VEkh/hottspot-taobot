#ifndef OANDA__TAO_BOT_update_account_snapshot
#define OANDA__TAO_BOT_update_account_snapshot

#include "get_account_snapshot.cpp" // get_account_snapshot
#include "tao_bot.h"                // Oanda::TaoBot
#include <ctime>                    // std::time

void Oanda::TaoBot::update_account_snapshot() {
  this->account_snapshot = get_account_snapshot(this->account_snapshot);
}

#endif
