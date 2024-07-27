#ifndef OANDA__TAO_BOT_update_account_snapshot
#define OANDA__TAO_BOT_update_account_snapshot

#include "lib/utils/time.cpp" // ::utils::time_
#include "tao_bot.h"          // Oanda::TaoBot
#include <time.h>             // time

void Oanda::TaoBot::update_account_snapshot() {
  this->account_snapshot = this->db_account_stat.get_snapshot({
      .api_key_id = this->api_client.config.account_id,
      .start_at =
          ::utils::time_::beginning_of_day_to_epoch((long int)time(nullptr)),
  });
}

#endif
