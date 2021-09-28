#ifndef OANDA__TAO_BOT_loss_to_recover
#define OANDA__TAO_BOT_loss_to_recover

/*
 * Oanda::TaoBot
 * closed_positions_stats_t
 */
#include "tao_bot.h"

#include "build_closed_positions_stats.cpp" // build_closed_positions_stats

double Oanda::TaoBot::loss_to_recover() {
  const closed_positions_stats_t stats = build_closed_positions_stats();

  return stats.current_balance - stats.max_balance;
}

#endif
